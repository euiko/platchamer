#ifndef ECS_REGISTRY_HPP
#define ECS_REGISTRY_HPP

#include <unordered_map>
#include <functional>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <type_traits>

#ifndef ECS_TICK_TYPE
#define ECS_TICK_TYPE ecs::DefaultTickData
#endif

#ifndef ECS_ALLOCATOR_TYPE
#define ECS_ALLOCATOR_TYPE std::allocator<ecs::Entity>
#endif


#ifndef ECS_NO_RTTI

#include <typeindex>
#include <typeinfo>
#define ECS_TYPE_IMPLEMENTATION

#else
#warning "RTTI Disabled"
#define ECS_TYPE_IMPLEMENTATION  \
	ecs::TypeIndex ecs::core::TypeRegistry::nextIndex = 1; \
	ECS_DEFINE_TYPE(ecs::events::OnEntityCreated); \
	ECS_DEFINE_TYPE(ecs::events::OnEntityDestroyed); \

#endif

namespace ecs {

#ifndef ECS_NO_RTTI
	typedef std::type_index TypeIndex;

#define ECS_DECLARE_TYPE
#define ECS_DEFINE_TYPE(name)

	template<typename T>
	TypeIndex getTypeIndex()
	{
		return std::type_index(typeid(T));
	}

#else
	typedef uint32_t TypeIndex;

	namespace core
	{
		class TypeRegistry
		{
		public:
			TypeRegistry()
			{
				index = nextIndex;
				++nextIndex;
			}

			TypeIndex getIndex() const
			{
				return index;
			}

		private:
			static TypeIndex nextIndex;
			TypeIndex index;
		};
	}

#define ECS_DECLARE_TYPE public: static ecs::core::TypeRegistry __ecs_type_reg
#define ECS_DEFINE_TYPE(name) ecs::core::TypeRegistry name::__ecs_type_reg

	template<typename T>
	TypeIndex getTypeIndex()
	{
		return T::__ecs_type_reg.getIndex();
    }
#endif


	class Registry;
    class Entity;

    typedef float DefaultTickData;
    typedef ECS_ALLOCATOR_TYPE Allocator;

    namespace core {
        template<typename... Types>
		class EntityComponentView;

        class EntityView;

        struct BaseComponentContainer 
        {
        public:
            virtual ~BaseComponentContainer() { }
			virtual void destroy(Registry* registry) = 0;
            virtual void removed(Entity* ent) = 0;

        };


		class BaseEventSubscriber
		{
		public:
			virtual ~BaseEventSubscriber() {};
        };

        template<typename... Types>
		class EntityComponentIterator
		{
		public:
			EntityComponentIterator(Registry* registry, size_t index, bool bIsEnd, bool bIncludePendingDestroy); // Inline

			size_t getIndex() const
			{
				return m_index;
			}

			bool isEnd() const; // Inline

			bool includePendingDestroy() const
			{
				return m_bIncludePendingDestroy;
			}

			Registry* getRegistry() const
			{
				return m_registry;
			}

			Entity* get() const;

			Entity* operator*() const
			{
				return get();
			}

			bool operator==(const EntityComponentIterator<Types...>& other) const
			{
				if (m_registry != other.m_registry)
					return false;

				if (isEnd())
					return other.isEnd();

				return m_index == other.m_index;
			}

			bool operator!=(const EntityComponentIterator<Types...>& other) const
			{
				if (m_registry != other.m_registry)
					return true;

				if (isEnd())
					return !other.isEnd();

				return m_index != other.m_index;
			}

			EntityComponentIterator<Types...>& operator++();

		private:
			bool m_bIsEnd = false;
			size_t m_index;
			class ecs::Registry* m_registry;
			bool m_bIncludePendingDestroy;
        };

        template<typename... Types>
		class EntityComponentView
		{
		public:
			EntityComponentView(const EntityComponentIterator<Types...>& first, const EntityComponentIterator<Types...>& last); // Inline

			const EntityComponentIterator<Types...>& begin() const
			{
				return m_firstItr;
			}

			const EntityComponentIterator<Types...>& end() const
			{
				return m_lastItr;
			}

		private:
			EntityComponentIterator<Types...> m_firstItr;
			EntityComponentIterator<Types...> m_lastItr;
        };

    };

	template<typename T>
	class ComponentHandle
	{
	public:
		ComponentHandle()
			: m_component(nullptr)
		{
		}

		ComponentHandle(T* component)
			: m_component(component)
		{
		}

		T* operator->() const
		{
			return m_component;
		}

		operator bool() const
		{
			return isValid();
		}

		T& get()
		{
			return *m_component;
		}

		bool isValid() const
		{
			return m_component != nullptr;
		}

	private:
		T* m_component;
    };

	class EntitySystem
	{
	public:
		virtual ~EntitySystem() {}

		virtual void configure(Registry* registry)
		{
		}

		virtual void unconfigure(Registry* registry)
		{
		}

#ifdef ECS_TICK_TYPE_VOID
		virtual void tick(Registry* registry)
#else
		virtual void tick(Registry* registry, ECS_TICK_TYPE data)
#endif
		{
		}
    };

    template<typename T>
    class EventSubscriber : public core::BaseEventSubscriber
    {
    public:
        virtual ~EventSubscriber() {}

        virtual void receive(Registry* registry, const T& event) = 0;
    };

    namespace events
	{
		// Called when a new entity is created.
		struct OnEntityCreated
		{
			ECS_DECLARE_TYPE;

			Entity* entity;
		};

		// Called when an entity is about to be destroyed.
		struct OnEntityDestroyed
		{
			ECS_DECLARE_TYPE;

			Entity* entity;
		};

		// Called when a component is assigned (not necessarily created).
		template<typename T>
		struct OnComponentAssigned
		{
			ECS_DECLARE_TYPE;

			Entity* entity;
			ComponentHandle<T> component;
		};

		// Called when a component is removed
		template<typename T>
		struct OnComponentRemoved
		{
			ECS_DECLARE_TYPE;

			Entity* entity;
			ComponentHandle<T> component;
		};

#ifdef ECS_NO_RTTI
		template<typename T>
		ECS_DEFINE_TYPE(ecs::events::OnComponentAssigned<T>);
		template<typename T>
		ECS_DEFINE_TYPE(ecs::events::OnComponentRemoved<T>);
#endif

    }



    class Registry 
    {
    public:
        using RegistryAllocator = std::allocator_traits<Allocator>::template rebind_alloc<Registry>;
		using EntityAllocator = std::allocator_traits<Allocator>::template rebind_alloc<Entity>;
		using SystemAllocator = std::allocator_traits<Allocator>::template rebind_alloc<EntitySystem>;
		using EntityPtrAllocator = std::allocator_traits<Allocator>::template rebind_alloc<Entity*>;
		using SystemPtrAllocator = std::allocator_traits<Allocator>::template rebind_alloc<EntitySystem*>;
		using SubscriberPtrAllocator = std::allocator_traits<Allocator>::template rebind_alloc<core::BaseEventSubscriber*>;
        using SubscriberPairAllocator = std::allocator_traits<Allocator>::template 
            rebind_alloc<std::pair<const TypeIndex, std::vector<core::BaseEventSubscriber*, SubscriberPtrAllocator>>>;
        
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

        ~Registry();

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

        bool cleanup();

        void reset();

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
        void each(typename std::common_type<std::function<void(Entity*, ComponentHandle<Types>...)>>::type viewFunc, bool bIncludePendingDestroy = false);

        void all(std::function<void(Entity*)> viewFunc, bool bIncludePendingDestroy = false);

        template<typename... Types>
		core::EntityComponentView<Types...> each(bool bIncludePendingDestroy = false)
		{
			core::EntityComponentIterator<Types...> first(this, 0, false, bIncludePendingDestroy);
			core::EntityComponentIterator<Types...> last(this, getCount(), true, bIncludePendingDestroy);
			return core::EntityComponentView<Types...>(first, last);
		}

		core::EntityView all(bool bIncludePendingDestroy = false);

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

        Entity* getById(size_t id) const;

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
			std::vector<core::BaseEventSubscriber*, SubscriberPtrAllocator>,
			std::hash<TypeIndex>,
			std::equal_to<TypeIndex>,
			SubscriberPairAllocator> m_subscribers;

        size_t lastEntityId = 0;
    };

    class Entity 
    {

	public:
		friend class Registry;

		const static size_t InvalidEntityId = 0;

		Entity(Registry* registry, size_t id)
			: m_registry(registry), m_id(id)
		{
		}

		~Entity()
		{
			removeAll();
		}

		Registry* getRegistry() const
		{
			return m_registry;
		}

		template<typename T>
		bool has() const
		{
			auto index = getTypeIndex<T>();
			return m_components.find(index) != m_components.end();
		}

		template<typename T, typename V, typename... Types>
		bool has() const
		{
			return has<T>() && has<V, Types...>();
		}

		template<typename T, typename... Args>
		ComponentHandle<T> assign(Args&&... args);

		template<typename T>
		bool remove()
		{
			auto found = m_components.find(getTypeIndex<T>());
			if (found != m_components.end())
			{
				found->second->removed(this);
				found->second->destroy(m_registry);

				m_components.erase(found);

				return true;
			}

			return false;
		}

		void removeAll()
		{
			for (auto pair : m_components)
			{
				pair.second->removed(this);
				pair.second->destroy(m_registry);
			}

			m_components.clear();
		}

		template<typename T>
		ComponentHandle<T> get();

		template<typename... Types>
		bool with(typename std::common_type<std::function<void(ComponentHandle<Types>...)>>::type view)
		{
			if (!has<Types...>())
				return false;

			view(get<Types>()...); 
			return true;
		}

		size_t getEntityId() const
		{
			return m_id;
		}

		bool isPendingDestroy() const
		{
			return m_bPendingDestroy;
        }

    private:
        
		std::unordered_map<TypeIndex, core::BaseComponentContainer*> m_components;
		Registry* m_registry;
		size_t m_id;
        bool m_bPendingDestroy = false;
    };


	namespace core
	{
		class EntityIterator
		{
		public:
			EntityIterator(Registry* registry, size_t index, bool bIsEnd, bool bIncludePendingDestroy); //Inline

			size_t getIndex() const
			{
				return m_index;
			}

			bool isEnd() const; // Inline

			bool includePendingDestroy() const
			{
				return m_bIncludePendingDestroy;
			}

			Registry* getRegistry() const
			{
				return m_registry;
			}

			Entity* get() const;

			Entity* operator*() const
			{
				return get();
			}

			bool operator==(const EntityIterator& other) const
			{
				if (m_registry != other.m_registry)
					return false;

				if (isEnd())
					return other.isEnd();

				return m_index == other.m_index;
			}

			bool operator!=(const EntityIterator& other) const
			{
				if (m_registry != other.m_registry)
					return true;

				if (isEnd())
					return !other.isEnd();

				return m_index != other.m_index;
			}

			EntityIterator& operator++();

		private:
			bool m_bIsEnd = false;
			size_t m_index;
			class ecs::Registry* m_registry;
			bool m_bIncludePendingDestroy;
		};

		class EntityView
		{
		public:
			EntityView(const EntityIterator& first, const EntityIterator& last)
				: m_firstItr(first), m_lastItr(last)
			{
				if (m_firstItr.get() == nullptr || (m_firstItr.get()->isPendingDestroy() && !m_firstItr.includePendingDestroy()))
				{
					++m_firstItr;
				}
			}

			const EntityIterator& begin() const
			{
				return m_firstItr;
			}

			const EntityIterator& end() const
			{
				return m_lastItr;
			}

		private:
			EntityIterator m_firstItr;
			EntityIterator m_lastItr;
		};

		template<typename T>
		struct ComponentContainer : public BaseComponentContainer
		{
			ComponentContainer() {}
			ComponentContainer(const T& data) : data(data) {}

			T data;

		protected:
			virtual void destroy(Registry* registry)
			{
				using ComponentAllocator = std::allocator_traits<Registry::EntityAllocator>::template rebind_alloc<ComponentContainer<T>>;

				ComponentAllocator alloc(registry->getPrimaryAllocator());
				std::allocator_traits<ComponentAllocator>::destroy(alloc, this);
				std::allocator_traits<ComponentAllocator>::deallocate(alloc, this, 1);
			}

			virtual void removed(Entity* ent)
			{
				auto handle = ComponentHandle<T>(&data);
				ent->getRegistry()->emit<events::OnComponentRemoved<T>>({ ent, handle });
			}
		};
    }

    inline Registry::~Registry()
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

	inline void Registry::destroy(Entity* ent, bool immediate)
	{
		if (ent == nullptr)
			return;

		if (ent->isPendingDestroy())
		{
			if (immediate)
			{
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

	inline bool Registry::cleanup()
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

	inline void Registry::reset()
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

	inline void Registry::all(std::function<void(Entity*)> viewFunc, bool bIncludePendingDestroy)
	{
		for (auto* ent : all(bIncludePendingDestroy))
		{
			viewFunc(ent);
		}
    }

    inline core::EntityView Registry::all(bool bIncludePendingDestroy)
	{
		core::EntityIterator first(this, 0, false, bIncludePendingDestroy);
		core::EntityIterator last(this, getCount(), true, bIncludePendingDestroy);
		return core::EntityView(first, last);
	}

	inline Entity* Registry::getById(size_t id) const
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

	template<typename... Types>
	void Registry::each(typename std::common_type<std::function<void(Entity*, ComponentHandle<Types>...)>>::type viewFunc, bool bIncludePendingDestroy)
	{
		for (auto* ent : each<Types...>(bIncludePendingDestroy))
		{
			viewFunc(ent, ent->template get<Types>()...);
		}
	}

	template<typename T, typename... Args>
	ComponentHandle<T> Entity::assign(Args&&... args)
	{
		using ComponentAllocator = std::allocator_traits<Registry::EntityAllocator>::template rebind_alloc<core::ComponentContainer<T>>;

		auto found = m_components.find(getTypeIndex<T>());
		if (found != m_components.end())
		{
			core::ComponentContainer<T>* container = reinterpret_cast<core::ComponentContainer<T>*>(found->second);
			container->data = T(args...);

			auto handle = ComponentHandle<T>(&container->data);
			m_registry->emit<events::OnComponentAssigned<T>>({ this, handle });
			return handle;
		}
		else
		{
			ComponentAllocator alloc(m_registry->getPrimaryAllocator());

			core::ComponentContainer<T>* container = std::allocator_traits<ComponentAllocator>::allocate(alloc, 1);
			std::allocator_traits<ComponentAllocator>::construct(alloc, container, T(args...));

			m_components.insert({ getTypeIndex<T>(), container });

			auto handle = ComponentHandle<T>(&container->data);
			m_registry->emit<events::OnComponentAssigned<T>>({ this, handle });
			return handle;
		}
    }

    template<typename T>
	ComponentHandle<T> Entity::get()
	{
		auto found = m_components.find(getTypeIndex<T>());
		if (found != m_components.end())
		{
			return ComponentHandle<T>(&reinterpret_cast<core::ComponentContainer<T>*>(found->second)->data);
		}
	
		return ComponentHandle<T>();
	}

    namespace core
	{
		inline EntityIterator::EntityIterator(class Registry* registry, size_t index, bool bIsEnd, bool bIncludePendingDestroy)
			: m_bIsEnd(bIsEnd), m_index(index), m_registry(registry), m_bIncludePendingDestroy(bIncludePendingDestroy)
		{
			if (index >= m_registry->getCount())
				this->m_bIsEnd = true;
		}

		inline bool EntityIterator::isEnd() const
		{
			return m_bIsEnd || m_index >= m_registry->getCount();
		}

		inline Entity* EntityIterator::get() const
		{
			if (isEnd())
				return nullptr;

			return m_registry->getByIndex(m_index);
		}

		inline EntityIterator& EntityIterator::operator++()
		{
			++m_index;
			while (m_index < m_registry->getCount() && (get() == nullptr || (get()->isPendingDestroy() && !m_bIncludePendingDestroy)))
			{
				++m_index;
			}

			if (m_index >= m_registry->getCount())
				m_bIsEnd = true;

			return *this;
		}

		template<typename... Types>
		EntityComponentIterator<Types...>::EntityComponentIterator(Registry* registry, size_t index, bool bIsEnd, bool bIncludePendingDestroy)
			: m_bIsEnd(bIsEnd), m_index(index), m_registry(registry), m_bIncludePendingDestroy(bIncludePendingDestroy)
		{
			if (m_index >= m_registry->getCount())
				this->m_bIsEnd = true;
		}

		template<typename... Types>
		bool EntityComponentIterator<Types...>::isEnd() const
		{
			return m_bIsEnd || m_index >= m_registry->getCount();
		}

		template<typename... Types>
		Entity* EntityComponentIterator<Types...>::get() const
		{
			if (isEnd())
				return nullptr;

			return m_registry->getByIndex(m_index);
		}

		template<typename... Types>
		EntityComponentIterator<Types...>& EntityComponentIterator<Types...>::operator++()
		{
			++m_index;
			while (m_index < m_registry->getCount() && (get() == nullptr || !get()->template has<Types...>() || (get()->isPendingDestroy() && !m_bIncludePendingDestroy)))
			{
				++m_index;
			}

			if (m_index >= m_registry->getCount())
				m_bIsEnd = true;

			return *this;
		}

		template<typename... Types>
		EntityComponentView<Types...>::EntityComponentView(const EntityComponentIterator<Types...>& first, const EntityComponentIterator<Types...>& last)
			: m_firstItr(first), m_lastItr(last)
		{
			if (m_firstItr.get() == nullptr || (m_firstItr.get()->isPendingDestroy() && !m_firstItr.includePendingDestroy())
				|| !m_firstItr.get()->template has<Types...>())
			{
				++m_firstItr;
			}
		}
    }

}

#endif