#include "rigid_body.hpp"
#include "../../../components/polygon_component.hpp"

namespace physics
{
    namespace ecs
    {
        void computePolygonMass(::ecs::Entity* entity, float density)
        {
            ::ecs::ComponentHandle<PolygonColliderComponent> collider = entity->get<PolygonColliderComponent>();
            ::ecs::ComponentHandle<RigidBodyComponent> rigid_body = entity->get<RigidBodyComponent>();
            
            Vect2 c( 0.0f, 0.0f ); // centroid
            float area = 0.0f;
            float I = 0.0f;
            const float k_inv3 = 1.0f / 3.0f;

            for(uint32_t i1 = 0; i1 < collider->m_vertexCount; ++i1)
            {
                Vect2 p1( collider->m_vertices[i1] );
                uint32_t i2 = i1 + 1 < collider->m_vertexCount ? i1 + 1 : 0;
                Vect2 p2( collider->m_vertices[i2] );

                float D = p1.cross(p2);
                float triangleArea = 0.5f * D;

                area += triangleArea;

                c += triangleArea * k_inv3 * (p1 + p2);

                float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
                float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
                I += (0.25f * k_inv3 * D) * (intx2 + inty2);
            }

            c *= 1.0f / area;

            for(uint32_t i = 0; i < collider->m_vertexCount; ++i)
                collider->m_vertices[i] -= c;
            
            ::ecs::ComponentHandle<PolygonComponent> polygon = entity->get<PolygonComponent>();
            if(polygon.isValid())
            {
                polygon->points = collider->m_vertices;
            }

            rigid_body->mass = density * area;
            rigid_body->inverse_mass = (rigid_body->mass) ? 1.0f / rigid_body->mass : 0.0f;
            rigid_body->inertia = I * density;
            rigid_body->inverse_inertia = rigid_body->inertia ? 1.0f / rigid_body->inertia : 0.0f;
        }

        void applyForce( const ::ecs::ComponentHandle<RigidBodyComponent>& rigid_body, const Vect2& f )
        {
            rigid_body->force += f;
        }

        void applyImpulse ( const ::ecs::ComponentHandle<RigidBodyComponent>& rigid_body, const Vect2& impulse, const Vect2& contactVector )
        {
            rigid_body->velocity += rigid_body->inverse_mass * impulse;
            float result = cross(contactVector, impulse );
            rigid_body->angular_velocity += rigid_body->inverse_inertia * result;
        }

        Vect2 getPolygonSupport( const ::ecs::ComponentHandle<PolygonColliderComponent> collider, const Vect2& dir )
        {
            float bestProjection = -FLT_MAX;
            Vect2 bestVertex;

            for(uint32_t i = 0; i < collider->m_vertexCount; ++i)
            {
                Vect2 v = collider->m_vertices[i];
                float projection = v.dot(dir);

                if(projection > bestProjection)
                {
                    bestVertex = v;
                    bestProjection = projection;
                }
            }

            return bestVertex;
        }
    }
}