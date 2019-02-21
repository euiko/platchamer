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


    void initialize( void )
    {
        computeMass( 1.0f );
    }

    void computeMass( float density )
    {
        body->m = M_PI * radius * radius * density;
        body->im = (body->m) ? 1.0f / body->m : 0.0f;
        body->I = body->m * radius * radius;
        body->iI = (body->I) ? 1.0f / body->I : 0.0f;
    }

    void setOrient( float radians )
    {
    }

    Type getType( void ) const
    {
        return colliderCircle;
    }
};

#endif
