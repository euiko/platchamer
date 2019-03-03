#ifndef RIGID_BODY_COMPONENT_HPP
#define RIGID_BODY_COMPONENT_HPP

#include "../types/vect2.hpp"
#include "../core/ecs/registry.hpp"

struct RigidBodyComponent
{
    
    ECS_DECLARE_TYPE;

    RigidBodyComponent(bool is_static = false) : is_static(is_static)
    {
    }

    Vect2 velocity;
    float angular_velocity;
    float torque;
    float orient;
    Vect2 force;

    bool is_static;
    
    float inertia;
    float inverse_inertia;
    float mass;
    float inverse_mass;

    float static_friction;
    float dynamic_friction;
    float restitution;
};

#endif