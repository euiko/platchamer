#ifndef PLATCHAMER_CORE_ECS_BASE_BASECOMPONENTCONTAINER_HPP
#define PLATCHAMER_CORE_ECS_BASE_BASECOMPONENTCONTAINER_HPP

#include "../forward.hpp"

namespace ecs
{
    namespace base
    {
        struct BaseComponentContainer 
        {
        public:
            virtual ~BaseComponentContainer() { }
			virtual void destroy(Registry* registry) = 0;
            virtual void removed(Entity* ent) = 0;

        };
    }
}

#endif