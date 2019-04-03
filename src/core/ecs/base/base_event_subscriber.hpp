#ifndef PLATCHAMER_CORE_ECS_BASE_BASEEVENTSUBSCRIBER_HPP
#define PLATCHAMER_CORE_ECS_BASE_BASEEVENTSUBSCRIBER_HPP

#include "../forward.hpp"

namespace ecs
{
    namespace base
    {

		class BaseEventSubscriber
		{
		public:
			virtual ~BaseEventSubscriber() {};
        };
    }
}

#endif