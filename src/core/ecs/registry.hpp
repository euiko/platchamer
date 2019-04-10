#ifndef ECS_REGISTRY_HPP
#define ECS_REGISTRY_HPP



#include "entity.hpp"
#include "entity_system.hpp"
#include "event_subscriber.hpp"
#include "events/on_component_assigned.hpp"
#include "events/on_component_removed.hpp"
#include "events/on_entity_created.hpp"
#include "events/on_entity_destroyed.hpp"
#include "base/entity_view.hpp"
#include "forward.hpp"

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
        
		void destroyRegistry();

		Registry(Allocator alloc);

        ~Registry();

        Entity* create();
        
        void destroy(Entity* ent, bool immediate = false);

        bool cleanup();

        void reset();

        EntitySystem* registerSystem(EntitySystem* system);
        void unregisterSystem(EntitySystem* system);

		void enableSystem(EntitySystem* system);

		void disableSystem(EntitySystem* system);

        template<typename T>
		void subscribe(EventSubscriber<T>* subscriber);

        template<typename T>
		void unsubscribe(EventSubscriber<T>* subscriber);

		void unsubscribeAll(void* subscriber);

        template<typename T>
		void emit(const T& event);

        template<typename... Types>
        void each(typename std::common_type<std::function<void(Entity*, ComponentHandle<Types>...)>>::type viewFunc, bool bIncludePendingDestroy = false);

        void all(std::function<void(Entity*)> viewFunc, bool bIncludePendingDestroy = false);

        template<typename... Types>
		base::EntityComponentView<Types...> each(bool bIncludePendingDestroy = false);

		base::EntityView all(bool bIncludePendingDestroy = false);

		size_t getCount() const;

		Entity* getByIndex(size_t idx);

        Entity* getById(size_t id) const;

#ifdef ECS_TICK_TYPE_VOID
		void tick();
#else
		void tick(ECS_TICK_TYPE data);
#endif

		EntityAllocator& getPrimaryAllocator();

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

};

#endif