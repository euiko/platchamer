#ifndef CIRCLE_COLLIDER_HPP
#define CIRCLE_COLLIDER_HPP

#include "collider_shape.hpp"
#include "../rigid_body.hpp"

struct CircleCollider : public ColliderShape
{
    CircleCollider( float r )
    {
        radius = r;
    }

    CircleCollider *Clone( void ) const
    {
        return new CircleCollider( radius );
    }

    RigidBody computeMass( float density )
    {
        RigidBody rigidBody;
        rigidBody.mass = M_PI * radius * radius * density;
        rigidBody.inverse_mass = rigidBody.mass ? 1.0f / rigidBody.mass : 0.0f;
        rigidBody.inertia = rigidBody.mass * radius * radius;
        rigidBody.inverse_inertia = rigidBody.inertia ? 1.0f / rigidBody.inertia : 0.0f;
        return rigidBody;
    }

    void SetOrient( real radians )
    {
    }

    Type getType( void ) const
    {
        return colliderCircle;
    }
};

#endif
