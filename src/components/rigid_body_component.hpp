#ifndef RIGID_BODY_COMPONENT_HPP
#define RIGID_BODY_COMPONENT_HPP

#include "../types/vect2.hpp"
#include "../libs/entcosy/src/entcosy/registry.hpp"

struct RigidBodyComponent
{
    
    ECS_DECLARE_TYPE;

    RigidBodyComponent(bool is_static = false) 
        : density(1.0f), static_friction(0.5f), dynamic_friction(0.3f),  
        restitution(0.2f), is_static(is_static)
    {
    }

    RigidBodyComponent(float density, float static_friction = 0.5f, 
        float dynamic_friction = 0.3f, float restitution = 0.2f, bool is_static = false
    ) : density(density), static_friction(static_friction), dynamic_friction(dynamic_friction),  
        restitution(restitution), is_static(is_static)
    {
    }

    Vect2 velocity;
    float angular_velocity;
    float torque;
    float orient;
    Vect2 force;

    bool is_static;
    float density;
    
    float inertia;
    float inverse_inertia;
    float mass;
    float inverse_mass;

    float static_friction;
    float dynamic_friction;
    float restitution;
};

#endif