#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "../core/ecs/registry.hpp"
#include "../components/physics_component.hpp"

using namespace ecs;
class PhysicsSystem: public EntitySystem,
    public EventSubscriber<events::OnComponentAssigned<PhysicsComponent>>
{

    ~PhysicsSystem() {};

    

};

#endif