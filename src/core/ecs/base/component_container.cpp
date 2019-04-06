#include "component_container.hpp"
#include "../registry.hpp"
#include "../entity.hpp"

namespace ecs
{
    namespace base
    {
        template<typename T>
        void ComponentContainer<T>::destroy(Registry* registry)
        {
            using ComponentAllocator = std::allocator_traits<Registry::EntityAllocator>::template rebind_alloc<ComponentContainer<T>>;

            ComponentAllocator alloc(registry->getPrimaryAllocator());
            std::allocator_traits<ComponentAllocator>::destroy(alloc, this);
            std::allocator_traits<ComponentAllocator>::deallocate(alloc, this, 1);
        }

        template<typename T>
        void ComponentContainer<T>::removed(Entity* ent)
        {
            auto handle = ComponentHandle<T>(&data);
            ent->getRegistry()->emit<events::OnComponentRemoved<T>>({ ent, handle });
        }
    } // base
} // ecs
