#ifndef PHYSICS_ECS_COLLISION_HPP
#define PHYSICS_ECS_COLLISION_HPP

#include "../../../types/collider.hpp"
#include "../../../libs/entcosy/src/entcosy/registry.hpp"
#include "rigid_body.hpp"
#include "manifold.hpp"

namespace physics
{
    namespace ecs
    {

        typedef void (*CollisionCallback)( Manifold *m, std::shared_ptr<entcosy::Entity> a, std::shared_ptr<entcosy::Entity> b );

        extern CollisionCallback Dispatch[Collider::ColliderCount][Collider::ColliderCount];

        void CircletoCircle( Manifold *m, std::shared_ptr<entcosy::Entity> a, std::shared_ptr<entcosy::Entity> b );
        void CircletoPolygon( Manifold *m, std::shared_ptr<entcosy::Entity> a, std::shared_ptr<entcosy::Entity> b );
        void PolygontoCircle( Manifold *m, std::shared_ptr<entcosy::Entity> a, std::shared_ptr<entcosy::Entity> b );
        void PolygontoPolygon( Manifold *m, std::shared_ptr<entcosy::Entity> a, std::shared_ptr<entcosy::Entity> b );
    
    }
}

#endif