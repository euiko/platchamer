#ifndef PLATCHAMER_CORE_ECS_ENTITYSYSTEM_HPP
#define PLATCHAMER_CORE_ECS_ENTITYSYSTEM_HPP
#include "forward.hpp"

namespace ecs
{
    class EntitySystem
	{
	public:
		virtual ~EntitySystem() {}

		virtual void configure(Registry* registry)
		{
		}

		virtual void unconfigure(Registry* registry)
		{
		}

#ifdef ECS_TICK_TYPE_VOID
		virtual void tick(Registry* registry)
#else
		virtual void tick(Registry* registry, ECS_TICK_TYPE data)
#endif
		{
		}
    };
}

#endif 