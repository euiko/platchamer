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
			virtual void destroy(Registry* registry);

			virtual void removed(Entity* ent);
		};
    } // base
} // ecs


#endif