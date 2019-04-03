#ifndef PLATCHAMER_CORE_ECS_BASE_COMPONENTCONTAINER_HPP
#define PLATCHAMER_CORE_ECS_BASE_COMPONENTCONTAINER_HPP

#include "../forward.hpp"
#include "base_component_container.hpp"

namespace ecs
{
    namespace base
    {
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
    } // base
} // ecs


#endif