#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP
#include <stdint.h>
#include "../types/shape.hpp"
#include "../types/vect2.hpp"

struct PhysicsComponent
{
    PhysicsComponent( float mass, float inertia, float static_friction, float dynamic_friction, float restitution, bool is_static = false )
        : static_friction(static_friction), dynamic_friction(dynamic_friction), restitution(restitution),
        is_static(is_static), torque(0), angular_velocity(0), velocity({0, 0})
    {
    }

    Vect2 velocity;
    float angular_velocity;
    float torque;
    Vect2 force;

    bool is_static;

    float static_friction;
    float dynamic_friction;
    float restitution;

};


#endif