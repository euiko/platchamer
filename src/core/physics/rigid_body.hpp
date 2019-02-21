#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP

#include <cstdint>
#include "shapes/collider_shape.hpp"
#include "../../types/vect2.hpp"

struct RigidBody
{  
    RigidBody( ColliderShape *shape_, uint32_t x, uint32_t y );

    void ApplyForce( const Vect2& f )
    {
        force += f;
    }

    void ApplyImpulse( const Vect2& impulse, const Vect2& contactVector )
    {
        velocity += im * impulse;
        float result = cross(contactVector, impulse );
        angular_velocity += iI * result;
    }

    void SetStatic( void )
    {
        I = 0.0f;
        iI = 0.0f;
        m = 0.0f;
        im = 0.0f;
    }

    void SetOrient( float radians );

    Vect2 position;
    Vect2 velocity;

    float angular_velocity;
    float torque;
    float orient; // radians
    Vect2 force;

    bool is_static;
    // Set by shape
    float I;  // moment of inertia
    float iI; // inverse inertia
    float m;  // mass
    float im; // inverse masee


    float static_friction;
    float dynamic_friction;
    float restitution;

    // Shape interface
    ColliderShape *shape;
};

#endif