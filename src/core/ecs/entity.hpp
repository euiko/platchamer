#ifndef PLATCHAMER_CORE_ECS_ENTITY_HPP
#define PLATCHAMER_CORE_ECS_ENTITY_HPP


#include "registry.hpp"
#include "entity_system.hpp"
#include "event_subscriber.hpp"
#include "events/on_component_assigned.hpp"
#include "events/on_component_removed.hpp"
#include "events/on_entity_created.hpp"
#include "events/on_entity_destroyed.hpp"
#include "base/entity_view.hpp"
#include "base/component_container.hpp"
#include "forward.hpp"

namespace ecs {
    class Entity 
    {
	public:
		friend class Registry;

		const static size_t InvalidEntityId = 0;

		Entity(Registry* registry, size_t id);

		~Entity();

		Registry* getRegistry() const;

		template<typename T>
		bool has() const;

		template<typename T, typename V, typename... Types>
		bool has() const;

		template<typename T, typename... Args>
		ComponentHandle<T> assign(Args&&... args);

		template<typename T>
		bool remove();

		void removeAll();

		template<typename T>
		ComponentHandle<T> get();

		template<typename... Types>
		bool with(typename std::common_type<std::function<void(ComponentHandle<Types>...)>>::type view);

		size_t getEntityId() const;

		bool isPendingDestroy() const;

    private:
        
		std::unordered_map<TypeIndex, base::BaseComponentContainer*> m_components;
		Registry* m_registry;
		size_t m_id;
        bool m_bPendingDestroy = false;
    };
}
#endif