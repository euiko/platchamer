#ifndef PLATCHAMER_CORE_ECS_EVENTSUBSCRIBER_HPP
#define PLATCHAMER_CORE_ECS_EVENTSUBSCRIBER_HPP

#include "forward.hpp"
#include "base/base_event_subscriber.hpp"

namespace ecs
{
    template<typename T>
    class EventSubscriber : public base::BaseEventSubscriber
    {
    public:
        virtual ~EventSubscriber() {}

        virtual void receive(Registry* registry, const T& event) = 0;
    };
}
#endif