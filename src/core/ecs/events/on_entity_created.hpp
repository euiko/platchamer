#ifndef PLATCHAMER_CORE_ECS_EVENTS_ONENTITYCREATED_HPP
#define PLATCHAMER_CORE_ECS_EVENTS_ONENTITYCREATED_HPP

#include "../forward.hpp"

namespace ecs
{
    namespace events
    {
        struct OnEntityCreated
		{
			ECS_DECLARE_TYPE;

			Entity* entity;
		};
    } // events
} // ecs


#endif