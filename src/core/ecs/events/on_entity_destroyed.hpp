#ifndef PLATCHAMER_CORE_ECS_EVENTS_ONENTITYDESTROYED_HPP
#define PLATCHAMER_CORE_ECS_EVENTS_ONENTITYDESTROYED_HPP
#include "../forward.hpp"

namespace ecs
{
    namespace events
    {
        struct OnEntityDestroyed
		{
			ECS_DECLARE_TYPE;

			Entity* entity;
		};
    } // events
} // ecs

#endif