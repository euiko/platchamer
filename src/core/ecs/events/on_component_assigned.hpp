#ifndef PLATCHAMER_CORE_ECS_EVENTS_ONCOMPONENTASSIGNED_HPP
#define PLATCHAMER_CORE_ECS_EVENTS_ONCOMPONENTASSIGNED_HPP

#include "../forward.hpp"

namespace ecs
{
    namespace events
    {
        template<typename T>
		struct OnComponentAssigned
		{
			ECS_DECLARE_TYPE;

			Entity* entity;
			ComponentHandle<T> component;
		};
    } // events
} // ecs


#endif