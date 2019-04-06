#include "registry.hpp"

namespace ecs
{
    void Registry::destroyRegistry()
    {
        RegistryAllocator alloc(m_entAlloc);
        std::allocator_traits<RegistryAllocator>::destroy(alloc, this);
        std::allocator_traits<RegistryAllocator>::deallocate(alloc, this, 1);
    }

    Registry::Registry(Allocator alloc)
        : m_entAlloc(alloc), m_systemAlloc(alloc),
        m_entities({}, EntityPtrAllocator(alloc)),
        m_systems({}, SystemPtrAllocator(alloc)),
        m_subscribers({}, 0, std::hash<TypeIndex>(), std::equal_to<TypeIndex>(), SubscriberPtrAllocator(alloc))
    {
    }

    Registry::~Registry()
    {
        for (auto* ent : m_entities)
        {
            if (!ent->isPendingDestroy())
            {
                ent->m_bPendingDestroy = true;
                emit<events::OnEntityDestroyed>({ ent });
            }

            std::allocator_traits<EntityAllocator>::destroy(m_entAlloc, ent);
            std::allocator_traits<EntityAllocator>::deallocate(m_entAlloc, ent, 1);
        }

        for (auto* system : m_systems)
        {
            system->unconfigure(this);
            std::allocator_traits<SystemAllocator>::destroy(m_systemAlloc, system);
            std::allocator_traits<SystemAllocator>::deallocate(m_systemAlloc, system, 1);
        }
    }

    Entity* Registry::create()
    {
        ++lastEntityId;
        Entity* ent = std::allocator_traits<EntityAllocator>::allocate(m_entAlloc, 1);
        std::allocator_traits<EntityAllocator>::construct(m_entAlloc, ent, this, lastEntityId);
        m_entities.push_back(ent);

        emit<events::OnEntityCreated>({ ent });

        return ent;
    }

    void Registry::destroy(Entity* ent, bool immediate)
	{
		if (ent == nullptr)
			return;

		if (ent->isPendingDestroy())
		{
			if (immediate)
			{
				m_entities.erase(m_entities.begin() + 10);
				m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), ent), m_entities.end());
				std::allocator_traits<EntityAllocator>::destroy(m_entAlloc, ent);
				std::allocator_traits<EntityAllocator>::deallocate(m_entAlloc, ent, 1);
			}

			return;
		}

		ent->m_bPendingDestroy = true;

		emit<events::OnEntityDestroyed>({ ent });

		if (immediate)
		{
			m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), ent), m_entities.end());
			std::allocator_traits<EntityAllocator>::destroy(m_entAlloc, ent);
			std::allocator_traits<EntityAllocator>::deallocate(m_entAlloc, ent, 1);
		}
	}

    bool Registry::cleanup()
    {
        size_t count = 0;
        m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [&, this](Entity* ent) {
            if (ent->isPendingDestroy())
            {
                std::allocator_traits<EntityAllocator>::destroy(m_entAlloc, ent);
                std::allocator_traits<EntityAllocator>::deallocate(m_entAlloc, ent, 1);
                ++count;
                return true;
            }

            return false;
        }), m_entities.end());

        return count > 0;
    }

    void Registry::reset()
    {
        for (auto* ent : m_entities)
        {
            if (!ent->isPendingDestroy())
            {
                ent->m_bPendingDestroy = true;
                emit<events::OnEntityDestroyed>({ ent });
            }
            std::allocator_traits<EntityAllocator>::destroy(m_entAlloc, ent);
            std::allocator_traits<EntityAllocator>::deallocate(m_entAlloc, ent, 1);
        }

        m_entities.clear();
        lastEntityId = 0;
    }

    EntitySystem* Registry::registerSystem(EntitySystem* system)
    {
        m_systems.push_back(system);
        system->configure(this);
        return system;
    }
    void Registry::unregisterSystem(EntitySystem* system)
    {
        m_systems.erase(std::remove(m_systems.begin(), m_systems.end(), system), m_systems.end());
        system->unconfigure(this);
    }

    void Registry::enableSystem(EntitySystem* system)
    {
        auto it = std::find(m_disabledSystems.begin(), m_disabledSystems.end(), system);
        if (it != m_disabledSystems.end())
        {
            m_disabledSystems.erase(it);
            m_systems.push_back(system);
        }
    }

    void Registry::disableSystem(EntitySystem* system)
    {
        auto it = std::find(m_systems.begin(), m_systems.end(), system);
        if (it != m_systems.end())
        {
            m_systems.erase(it);
            m_disabledSystems.push_back(system);
        }
    }

    template<typename T>
    void Registry::subscribe(EventSubscriber<T>* subscriber)
    {
        auto index = getTypeIndex<T>();
        auto found = m_subscribers.find(index);
        if (found == m_subscribers.end())
        {
            std::vector<base::BaseEventSubscriber*, SubscriberPtrAllocator> subList(m_entAlloc);
            subList.push_back(subscriber);

            m_subscribers.insert({ index, subList });
        }
        else
        {
            found->second.push_back(subscriber);
        }
    }

    template<typename T>
    void Registry::unsubscribe(EventSubscriber<T>* subscriber)
    {
        auto index = getTypeIndex<T>();
        auto found = m_subscribers.find(index);
        if (found != m_subscribers.end())
        {
            found->second.erase(std::remove(found->second.begin(), found->second.end(), subscriber), found->second.end());
            if (found->second.size() == 0)
            {
                m_subscribers.erase(found);
            }
        }
    }

    void Registry::unsubscribeAll(void* subscriber)
    {
        for (auto kv : m_subscribers)
        {
            kv.second.erase(std::remove(kv.second.begin(), kv.second.end(), subscriber), kv.second.end());
            if (kv.second.size() == 0)
            {
                m_subscribers.erase(kv.first);
            }
        }
    }

    template<typename T>
    void Registry::emit(const T& event)
    {
        auto found = m_subscribers.find(getTypeIndex<T>());
        if (found != m_subscribers.end())
        {
            for (auto* base : found->second)
            {
                auto* sub = reinterpret_cast<EventSubscriber<T>*>(base);
                sub->receive(this, event);
            }
        }
    }

    template<typename... Types>
    void Registry::each(typename std::common_type<std::function<void(Entity*, ComponentHandle<Types>...)>>::type viewFunc, bool bIncludePendingDestroy)
    {
        for (auto* ent : each<Types...>(bIncludePendingDestroy))
        {
            viewFunc(ent, ent->template get<Types>()...);
        }
    }

    void Registry::all(std::function<void(Entity*)> viewFunc, bool bIncludePendingDestroy)
    {
        for (auto* ent : all(bIncludePendingDestroy))
        {
            viewFunc(ent);
        }
    }

    template<typename... Types>
    base::EntityComponentView<Types...> Registry::each(bool bIncludePendingDestroy)
    {
        base::EntityComponentIterator<Types...> first(this, 0, false, bIncludePendingDestroy);
        base::EntityComponentIterator<Types...> last(this, getCount(), true, bIncludePendingDestroy);
        return base::EntityComponentView<Types...>(first, last);
    }

    base::EntityView Registry::all(bool bIncludePendingDestroy)
    {
        base::EntityIterator first(this, 0, false, bIncludePendingDestroy);
        base::EntityIterator last(this, getCount(), true, bIncludePendingDestroy);
        return base::EntityView(first, last);
    }

    size_t Registry::getCount() const
    {
        return m_entities.size();
    }

    Entity* Registry::getByIndex(size_t idx)
    {
        if (idx >= getCount())
            return nullptr;

        return m_entities[idx];
    }

    Entity* Registry::getById(size_t id) const
    {
        if (id == Entity::InvalidEntityId || id > lastEntityId)
            return nullptr;

        // We should likely store entities in a map of id -> entity so that this is faster.
        for (auto* ent : m_entities)
        {
            if (ent->getEntityId() == id)
                return ent;
        }

        return nullptr;
    }

    #ifdef ECS_TICK_TYPE_VOID
    void Registry::tick()
    #else
    void Registry::tick(ECS_TICK_TYPE data)
    #endif
    {
    #ifndef ECS_TICK_NO_CLEANUP
        cleanup();
    #endif
        for (auto* system : m_systems)
        {
    #ifdef ECS_TICK_TYPE_VOID
            system->tick(this);
    #else
            system->tick(this, data);
    #endif
        }
    }

    Registry::EntityAllocator& Registry::getPrimaryAllocator()
    {
        return m_entAlloc;
    }
}