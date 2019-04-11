#ifndef PHYSICS_ECS_MANIFOLD_HPP
#define PHYSICS_ECS_MANIFOLD_HPP


#include "../../../libs/entcosy/src/entcosy/registry.hpp"
#include "../../../components/position_component.hpp"
#include "../../../components/rigid_body_component.hpp"
#include "../../../components/polygon_collider_component.hpp"

namespace physics
{
    namespace ecs
    {
        struct Manifold
        {
            Manifold( std::shared_ptr<entcosy::Entity> a, std::shared_ptr<entcosy::Entity> b, const Vect2& gravity = { 0.0f, 10.0f } );

            void solve( Collider* collider_A, Collider* collider_B );                 // Generate contact information
            void initialize( void );            // Precalculations for impulse solving
            void applyImpulse( void );          // Solve impulse and apply
            void positionalCorrection( void );  // Naive correction of positional penetration
            void infiniteMassCorrection( void );

            std::shared_ptr<entcosy::Entity> entity_A;
            std::shared_ptr<entcosy::Entity> entity_B;

            RigidBodyComponent* rigid_body_A;
            RigidBodyComponent* rigid_body_B;

            PolygonColliderComponent* polygon_collider_A;
            PolygonColliderComponent* polygon_collider_B;

            PositionComponent* position_A;
            PositionComponent* position_B;

            float penetration;     // Depth of penetration from collision
            Vect2 normal;          // From A to B
            Vect2 contacts[2];     // Points of contact during collision
            uint32_t contact_count; // Number of contacts that occured during collision
            float e;               // Mixed restitution
            float df;              // Mixed dynamic friction
            float sf;


            const Vect2 gravity;
            const float dt = 1.0f / 60.0f;
        };
    }
}

#endif