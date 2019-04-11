#ifndef PHYSICS_ECS_RIGID_BODY_HPP
#define PHYSICS_ECS_RIGID_BODY_HPP

#include <float.h>
#include "../../../types/collider.hpp"
#include "../../../libs/entcosy/src/entcosy/registry.hpp"
#include "../../../components/rigid_body_component.hpp"
#include "../../../components/polygon_collider_component.hpp"

namespace physics
{
    namespace ecs
    {

        typedef void (*ComputeMassCallback)( std::shared_ptr<entcosy::Entity> entity, float density );
        extern ComputeMassCallback ComputeMass[Collider::ColliderCount];

        void initPolygonVertices(std::shared_ptr<entcosy::Entity> entity);

        void computePolygonMass(std::shared_ptr<entcosy::Entity> entity, float density);

        void computeCircleMass(std::shared_ptr<entcosy::Entity> entity, float density);

        void applyForce( RigidBodyComponent* rigid_body, const Vect2& f );

        void applyImpulse( RigidBodyComponent* rigid_body, const Vect2& impulse, const Vect2& contactVector );

        Vect2 getPolygonSupport( PolygonColliderComponent* collider, const Vect2& dir );

        // void computeCircleMass(const ::ecs::ComponentHandle<PolygonColliderComponent>& collider, 
        //     ::ecs::ComponentHandle<RigidBodyComponent>& rigid_body, float density);
    }
}

#endif