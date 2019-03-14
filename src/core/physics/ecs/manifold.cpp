#include "manifold.hpp"
#include "rigid_body.hpp"
#include "collision.hpp"

namespace physics 
{
    namespace ecs
    {
        Manifold::Manifold( ::ecs::Entity* a, ::ecs::Entity* b, const Vect2& gravity )
            : entity_A(a), entity_B(b)
            , rigid_body_A(a->get<RigidBodyComponent>()), rigid_body_B(b->get<RigidBodyComponent>())
            , polygon_collider_A(a->get<PolygonColliderComponent>()), polygon_collider_B(b->get<PolygonColliderComponent>())
            , position_A(a->get<PositionComponent>()), position_B(b->get<PositionComponent>()), gravity(gravity)
        {
        }
        
        void Manifold::solve( void )
        {
            // if(rigid_body_A.isValid() && rigid_body_B.isValid())
            // {
            //     if(rigid_body_A->is_static && rigid_body_B->is_static)
            //         return;
            // }

            Collider collider_A = entity_A->get<PolygonColliderComponent>().get();
            Collider collider_B = entity_A->get<PolygonColliderComponent>().get();
            Dispatch[collider_A.colliderType][collider_B.colliderType]( this, entity_A, entity_B );
        }

        void Manifold::initialize( void )
        {
            e = std::min( rigid_body_A->restitution, rigid_body_B->restitution );

            sf = std::sqrt( rigid_body_A->static_friction * rigid_body_B->static_friction );
            df = std::sqrt( rigid_body_A->dynamic_friction * rigid_body_B->dynamic_friction );

            for(uint32_t i = 0; i < contact_count; ++i)
            {
                Vect2 ra = contacts[i] - position_A->pos;
                Vect2 rb = contacts[i] - position_B->pos;

                Vect2 rv = rigid_body_B->velocity + cross( rigid_body_B->angular_velocity, rb ) -
                        rigid_body_A->velocity - cross( rigid_body_A->angular_velocity, ra );

                if(rv.sqrLength( ) < (dt * gravity).sqrLength( ) + EPSILON)
                e = 0.0f;
            }
        }

        void Manifold::applyImpulse( void )
        {
            if(equal( rigid_body_A->inverse_mass + rigid_body_B->inverse_mass, 0 ))
            {
                infiniteMassCorrection( );
                return;
            }

            for(uint32_t i = 0; i < contact_count; ++i)
            {
                Vect2 ra = contacts[i] - position_A->pos;
                Vect2 rb = contacts[i] - position_B->pos;

                Vect2 rv = rigid_body_B->velocity + cross( rigid_body_B->angular_velocity, rb ) -
                        rigid_body_A->velocity - cross( rigid_body_A->angular_velocity, ra );

                float contactVel = rv.dot(normal);

                if(contactVel > 0)
                    return;

                float raCrossN = cross( ra, normal );
                float rbCrossN = cross( rb, normal );
                float invMassSum = rigid_body_A->inverse_mass + rigid_body_B->inverse_mass + sqr( raCrossN ) * 
                    rigid_body_A->inverse_inertia + sqr( rbCrossN ) * rigid_body_B->inverse_inertia;

                float j = -(1.0f + e) * contactVel;
                j /= invMassSum;
                j /= (float)contact_count;

                Vect2 impulse = normal * j;
                ecs::applyImpulse( rigid_body_A, -impulse, ra );
                ecs::applyImpulse( rigid_body_B, impulse, rb );

                rv = rigid_body_B->velocity + cross( rigid_body_B->angular_velocity, rb ) -
                    rigid_body_A->velocity - cross( rigid_body_A->angular_velocity, ra );

                Vect2 t = rv - (normal * rv.dot(normal));
                t.normalize( );

                float jt = -rv.dot(t);
                jt /= invMassSum;
                jt /= (float)contact_count;

                if(equal( jt, 0.0f ))
                    return;

                Vect2 tangentImpulse;
                if(std::abs( jt ) < j * sf)
                    tangentImpulse = t * jt;
                else
                    tangentImpulse = t * -j * df;

                ecs::applyImpulse( rigid_body_A, -tangentImpulse, ra );
                ecs::applyImpulse( rigid_body_B, tangentImpulse, rb );
            }
        }

        void Manifold::positionalCorrection( void )
        {
            const float k_slop = 0.05f;
            const float percent = 0.4f;
            Vect2 correction = (
                    std::max( penetration - k_slop, 0.0f ) 
                    / 
                    (rigid_body_A->inverse_mass + rigid_body_B->inverse_mass)
                ) * normal * percent;
            position_A->pos -= correction * rigid_body_A->inverse_mass;
            position_B->pos += correction * rigid_body_B->inverse_mass;
        }

        void Manifold::infiniteMassCorrection( void )
        {
            rigid_body_A->velocity = { 0, 0 };
            rigid_body_B->velocity = { 0, 0 };
        }
    }
}