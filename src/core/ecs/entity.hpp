#ifndef PLATCHAMER_CORE_ECS_ENTITY_HPP
#define PLATCHAMER_CORE_ECS_ENTITY_HPP

#include "forward.hpp"
#include "base/base_component_container.hpp"

namespace ecs {
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
		ComponentHandle<T> assign(Args&&... args)
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
		ComponentHandle<T> get()
		{
			auto found = m_components.find(getTypeIndex<T>());
			if (found != m_components.end())
			{
				return ComponentHandle<T>(&reinterpret_cast<core::ComponentContainer<T>*>(found->second)->data);
			}
		
			return ComponentHandle<T>();
		}

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
        
		std::unordered_map<TypeIndex, base::BaseComponentContainer*> m_components;
		Registry* m_registry;
		size_t m_id;
        bool m_bPendingDestroy = false;
    };
}
#endif