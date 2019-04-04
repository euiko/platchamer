#ifndef ECS_REGISTRY_HPP
#define ECS_REGISTRY_HPP

#include <unordered_map>
#include <functional>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <type_traits>

#include "forward.hpp"
#include "base/entity_view.hpp"
#include "entity.hpp"
#include "entity_system.hpp"

namespace ecs {

    class Registry 
    {
    public:
        using RegistryAllocator = std::allocator_traits<Allocator>::template rebind_alloc<Registry>;
		using EntityAllocator = std::allocator_traits<Allocator>::template rebind_alloc<Entity>;
		using SystemAllocator = std::allocator_traits<Allocator>::template rebind_alloc<EntitySystem>;
		using EntityPtrAllocator = std::allocator_traits<Allocator>::template rebind_alloc<Entity*>;
		using SystemPtrAllocator = std::allocator_traits<Allocator>::template rebind_alloc<EntitySystem*>;
		using SubscriberPtrAllocator = std::allocator_traits<Allocator>::template rebind_alloc<base::BaseEventSubscriber*>;
        using SubscriberPairAllocator = std::allocator_traits<Allocator>::template 
            rebind_alloc<std::pair<const TypeIndex, std::vector<base::BaseEventSubscriber*, SubscriberPtrAllocator>>>;
        
        static Registry* createRegistry(Allocator alloc)
		{
			RegistryAllocator registryAlloc(alloc);
			Registry* registry = std::allocator_traits<RegistryAllocator>::allocate(registryAlloc, 1);
			std::allocator_traits<RegistryAllocator>::construct(registryAlloc, registry, alloc);

			return registry;
		}

		static Registry* createRegistry()
		{
			return createRegistry(Allocator());
		}
        
		void destroyRegistry()
		{
			RegistryAllocator alloc(m_entAlloc);
			std::allocator_traits<RegistryAllocator>::destroy(alloc, this);
			std::allocator_traits<RegistryAllocator>::deallocate(alloc, this, 1);
		}

		Registry(Allocator alloc)
			: m_entAlloc(alloc), m_systemAlloc(alloc),
			m_entities({}, EntityPtrAllocator(alloc)),
			m_systems({}, SystemPtrAllocator(alloc)),
			m_subscribers({}, 0, std::hash<TypeIndex>(), std::equal_to<TypeIndex>(), SubscriberPtrAllocator(alloc))
		{
        }

        ~Registry()
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

        Entity* create()
		{
			++lastEntityId;
			Entity* ent = std::allocator_traits<EntityAllocator>::allocate(m_entAlloc, 1);
			std::allocator_traits<EntityAllocator>::construct(m_entAlloc, ent, this, lastEntityId);
			m_entities.push_back(ent);

			emit<events::OnEntityCreated>({ ent });

			return ent;
        }
        
        void destroy(Entity* ent, bool immediate = false);

        bool cleanup()
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

        void reset()
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

        EntitySystem* registerSystem(EntitySystem* system)
		{
			m_systems.push_back(system);
			system->configure(this);
            return system;
        }
        void unregisterSystem(EntitySystem* system)
		{
			m_systems.erase(std::remove(m_systems.begin(), m_systems.end(), system), m_systems.end());
			system->unconfigure(this);
		}

		void enableSystem(EntitySystem* system)
		{
			auto it = std::find(m_disabledSystems.begin(), m_disabledSystems.end(), system);
			if (it != m_disabledSystems.end())
			{
				m_disabledSystems.erase(it);
				m_systems.push_back(system);
			}
		}

		void disableSystem(EntitySystem* system)
		{
			auto it = std::find(m_systems.begin(), m_systems.end(), system);
			if (it != m_systems.end())
			{
				m_systems.erase(it);
				m_disabledSystems.push_back(system);
			}
        }

        template<typename T>
		void subscribe(EventSubscriber<T>* subscriber)
		{
			auto index = getTypeIndex<T>();
			auto found = m_subscribers.find(index);
			if (found == m_subscribers.end())
			{
				std::vector<core::BaseEventSubscriber*, SubscriberPtrAllocator> subList(m_entAlloc);
				subList.push_back(subscriber);

				m_subscribers.insert({ index, subList });
			}
			else
			{
				found->second.push_back(subscriber);
			}
		}

        template<typename T>
		void unsubscribe(EventSubscriber<T>* subscriber)
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

		void unsubscribeAll(void* subscriber)
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
		void emit(const T& event)
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
        void each(typename std::common_type<std::function<void(Entity*, ComponentHandle<Types>...)>>::type viewFunc, bool bIncludePendingDestroy)
		{
			for (auto* ent : each<Types...>(bIncludePendingDestroy))
			{
				viewFunc(ent, ent->template get<Types>()...);
			}
		}

        void all(std::function<void(Entity*)> viewFunc, bool bIncludePendingDestroy = false)
		{
			for (auto* ent : all(bIncludePendingDestroy))
			{
				viewFunc(ent);
			}
		}

        template<typename... Types>
		base::EntityComponentView<Types...> each(bool bIncludePendingDestroy = false)
		{
			base::EntityComponentIterator<Types...> first(this, 0, false, bIncludePendingDestroy);
			base::EntityComponentIterator<Types...> last(this, getCount(), true, bIncludePendingDestroy);
			return base::EntityComponentView<Types...>(first, last);
		}

		base::EntityView all(bool bIncludePendingDestroy = false)
		{
			base::EntityIterator first(this, 0, false, bIncludePendingDestroy);
			base::EntityIterator last(this, getCount(), true, bIncludePendingDestroy);
			return base::EntityView(first, last);
		}

		size_t getCount() const
		{
			return m_entities.size();
		}

		Entity* getByIndex(size_t idx)
		{
			if (idx >= getCount())
				return nullptr;

			return m_entities[idx];
        }

        Entity* getById(size_t id) const
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
		void tick()
#else
		void tick(ECS_TICK_TYPE data)
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

		EntityAllocator& getPrimaryAllocator()
		{
			return m_entAlloc;
        }


	private:
		EntityAllocator m_entAlloc;
		SystemAllocator m_systemAlloc;

		std::vector<Entity*, EntityPtrAllocator> m_entities;
		std::vector<EntitySystem*, SystemPtrAllocator> m_systems;
        	std::vector<EntitySystem*> m_disabledSystems;
		std::unordered_map<TypeIndex,
			std::vector<base::BaseEventSubscriber*, SubscriberPtrAllocator>,
			std::hash<TypeIndex>,
			std::equal_to<TypeIndex>,
			SubscriberPairAllocator> m_subscribers;

        size_t lastEntityId = 0;
    };

	inline void Registry::destroy(Entity* ent, bool immediate)
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



};

#endif