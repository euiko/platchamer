#ifndef PHYSICS_ECS_RIGID_BODY_HPP
#define PHYSICS_ECS_RIGID_BODY_HPP

#include "../../ecs/registry.hpp"
#include "../../../components/rigid_body_component.hpp"
#include "../../../components/polygon_collider_component.hpp"

namespace physics
{
    namespace ecs
    {
        void computePolygonMass(const ::ecs::ComponentHandle<PolygonColliderComponent>& collider, 
            const ::ecs::ComponentHandle<RigidBodyComponent>& rigid_body, float density);

        // void computeCircleMass(const ::ecs::ComponentHandle<PolygonColliderComponent>& collider, 
        //     ::ecs::ComponentHandle<RigidBodyComponent>& rigid_body, float density);
    }
}

#endif