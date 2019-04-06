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

		#ifdef ECS_NO_RTTI
		template<typename T>
		ECS_DEFINE_TYPE(ecs::events::OnComponentAssigned<T>);
		#endif
    } // events
} // ecs


#endif