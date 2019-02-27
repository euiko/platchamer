#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP
#include <stdint.h>
#include "../core/physics/shapes/collider_shape.hpp"
#include "../core/physics/rigid_body.hpp"
#include "../types/shape.hpp"
#include "../types/vect2.hpp"

struct PhysicsComponent
{
    ECS_DECLARE_TYPE;
    PhysicsComponent( ColliderShape *collider_shape, uint32_t x, uint32_t y, bool is_static = false )
        : rigid_body(new RigidBody(collider_shape, x, y)), is_static(is_static)
    {
    }

    RigidBody* rigid_body;
    bool is_static;

};


#endif