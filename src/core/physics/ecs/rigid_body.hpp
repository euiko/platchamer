#ifndef PHYSICS_ECS_RIGID_BODY_HPP
#define PHYSICS_ECS_RIGID_BODY_HPP

#include <float.h>
#include "../../../types/collider.hpp"
#include "../../ecs/registry.hpp"
#include "../../../components/rigid_body_component.hpp"
#include "../../../components/polygon_collider_component.hpp"

namespace physics
{
    namespace ecs
    {

        typedef void (*ComputeMassCallback)( ::ecs::Entity *entity, float density );
        extern ComputeMassCallback ComputeMass[Collider::ColliderCount];

        void initPolygonVertices(::ecs::Entity* entity);

        void computePolygonMass(::ecs::Entity* entity, float density);

        void computeCircleMass(::ecs::Entity* entity, float density);

        void applyForce( const ::ecs::ComponentHandle<RigidBodyComponent>& rigid_body, const Vect2& f );

        void applyImpulse( const ::ecs::ComponentHandle<RigidBodyComponent>& rigid_body, const Vect2& impulse, const Vect2& contactVector );

        Vect2 getPolygonSupport( const ::ecs::ComponentHandle<PolygonColliderComponent> collider, const Vect2& dir );

        // void computeCircleMass(const ::ecs::ComponentHandle<PolygonColliderComponent>& collider, 
        //     ::ecs::ComponentHandle<RigidBodyComponent>& rigid_body, float density);
    }
}

#endif