#include "rigid_body.hpp"

namespace physics
{
    namespace ecs
    {
        void computePolygonMass(const ::ecs::ComponentHandle<PolygonColliderComponent>& collider, 
            const ::ecs::ComponentHandle<RigidBodyComponent>& rigid_body, float density)
        {
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

            rigid_body->mass = density * area;
            rigid_body->inverse_mass = (rigid_body->mass) ? 1.0f / rigid_body->mass : 0.0f;
            rigid_body->inertia = I * density;
            rigid_body->inverse_inertia = rigid_body->inertia ? 1.0f / rigid_body->inertia : 0.0f;
        }
    }
}