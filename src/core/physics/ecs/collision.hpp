#ifndef PHYSICS_ECS_COLLISION_HPP
#define PHYSICS_ECS_COLLISION_HPP

#include "../../../types/collider.hpp"
#include "../../ecs.hpp"
#include "rigid_body.hpp"
#include "manifold.hpp"

namespace physics
{
    namespace ecs
    {

        typedef void (*CollisionCallback)( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b );

        extern CollisionCallback Dispatch[Collider::ColliderCount][Collider::ColliderCount];

        void CircletoCircle( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b );
        void CircletoPolygon( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b );
        void PolygontoCircle( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b );
        void PolygontoPolygon( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b );
    
    }
}

#endif