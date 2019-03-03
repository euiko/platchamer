#ifndef PHYSICS_ECS_MANIFOLD_HPP
#define PHYSICS_ECS_MANIFOLD_HPP


#include "../../ecs/registry.hpp"
#include "../../../components/position_component.hpp"
#include "../../../components/rigid_body_component.hpp"
#include "../../../components/polygon_collider_component.hpp"

namespace physics
{
    namespace ecs
    {
        struct Manifold
        {
            Manifold( ::ecs::Entity* a, ::ecs::Entity* b )
                : entity_A(a), entity_B(b)
                , rigid_body_A(a->get<RigidBodyComponent>()), rigid_body_B(b->get<RigidBodyComponent>())
                , polygon_collider_A(a->get<PolygonColliderComponent>()), polygon_collider_B(b->get<PolygonColliderComponent>())
                , position_A(a->get<PositionComponent>()), position_B(b->get<PositionComponent>())
            {
            }

            void solve( void );                 // Generate contact information
            void initialize( void );            // Precalculations for impulse solving
            void applyImpulse( void );          // Solve impulse and apply
            void positionalCorrection( void );  // Naive correction of positional penetration
            void infiniteMassCorrection( void );

            ::ecs::Entity* entity_A;
            ::ecs::Entity* entity_B;

            ::ecs::ComponentHandle<RigidBodyComponent> rigid_body_A;
            ::ecs::ComponentHandle<RigidBodyComponent> rigid_body_B;

            ::ecs::ComponentHandle<PolygonColliderComponent> polygon_collider_A;
            ::ecs::ComponentHandle<PolygonColliderComponent> polygon_collider_B;

            ::ecs::ComponentHandle<PositionComponent> position_A;
            ::ecs::ComponentHandle<PositionComponent> position_B;

            float penetration;     // Depth of penetration from collision
            Vect2 normal;          // From A to B
            Vect2 contacts[2];     // Points of contact during collision
            uint32_t contact_count; // Number of contacts that occured during collision
            float e;               // Mixed restitution
            float df;              // Mixed dynamic friction
            float sf;
        };
    }
}

#endif