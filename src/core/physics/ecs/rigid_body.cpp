#include <cassert>
#include <algorithm>
#include "rigid_body.hpp"
#include "../../../components/circle_collider_component.hpp"
#include "../../../components/polygon_component.hpp"

namespace physics
{
    namespace ecs
    {

        ComputeMassCallback ComputeMass[Collider::ColliderCount] = { computeCircleMass, computePolygonMass };

        void initPolygonVertices(std::shared_ptr<entcosy::Entity> entity)
        {
            PolygonColliderComponent* pollygonCollider = entity->get<PolygonColliderComponent>();
            int count = pollygonCollider->m_vertexCount;
            Vect2 vertices[count];
            std::copy(pollygonCollider->m_vertices.begin(), pollygonCollider->m_vertices.end(), vertices);
            
            assert( count > 2 && count <= MaxPolyVertexCount );
            count = std::min( (int32_t)count, MaxPolyVertexCount );

            int32_t rightMost = 0;
            float highestXCoord = vertices[0].x;
            for(uint32_t i = 1; i < count; ++i)
            {
                float x = vertices[i].x;
                if(x > highestXCoord)
                {
                    highestXCoord = x;
                    rightMost = i;
                }

                else if(x == highestXCoord)
                    if(vertices[i].y < vertices[rightMost].y)
                        rightMost = i;
            }

            int32_t hull[MaxPolyVertexCount];
            int32_t outCount = 0;
            int32_t indexHull = rightMost;

            for (;;)
            {
                hull[outCount] = indexHull;
                int32_t nextHullIndex = 0;
                for(int32_t i = 1; i < (int32_t)count; ++i)
                {
                    if(nextHullIndex == indexHull)
                    {
                        nextHullIndex = i;
                        continue;
                    }

                    Vect2 e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
                    Vect2 e2 = vertices[i] - vertices[hull[outCount]];
                    float c = e1.cross(e2);
                    if(c < 0.0f)
                        nextHullIndex = i;

                    if(c == 0.0f && e2.sqrLength( ) > e1.sqrLength( ))
                        nextHullIndex = i;
                }
                
                ++outCount;
                indexHull = nextHullIndex;

                if(nextHullIndex == rightMost)
                {
                    pollygonCollider->m_vertexCount = outCount;
                    pollygonCollider->m_normals.resize(outCount);
                    break;
                }
            }

            for(uint32_t i = 0; i < pollygonCollider->m_vertexCount; ++i)
                pollygonCollider->m_vertices[i] = vertices[hull[i]];

            for(uint32_t i1 = 0; i1 < pollygonCollider->m_vertexCount; ++i1)
            {
                uint32_t i2 = i1 + 1 < pollygonCollider->m_vertexCount ? i1 + 1 : 0;
                Vect2 face = pollygonCollider->m_vertices[i2] - pollygonCollider->m_vertices[i1];

                assert( face.sqrLength( ) > EPSILON * EPSILON );

                pollygonCollider->m_normals[i1] = Vect2( face.y, -face.x );
                pollygonCollider->m_normals[i1].normalize( );
            }
        }

        void computePolygonMass(std::shared_ptr<entcosy::Entity> entity, float density)
        {
            PolygonColliderComponent* collider = entity->get<PolygonColliderComponent>();
            RigidBodyComponent* rigid_body = entity->get<RigidBodyComponent>();
            
            Vect2 c( 0.0f, 0.0f ); 
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
            
            PolygonComponent* polygon = entity->get<PolygonComponent>();
            if(polygon != nullptr)
            {
                ::std::transform(polygon->points.begin(), polygon->points.end(), polygon->points.begin(), [&](Vect2& point)
                {
                    return point - c;
                });
            }

            if(rigid_body != nullptr)
            {
                rigid_body->mass = density * area;
                rigid_body->inverse_mass = (rigid_body->mass) ? 100.0f / rigid_body->mass : 0.0f;
                rigid_body->inertia = I * density;
                rigid_body->inverse_inertia = rigid_body->inertia ? 100.0f / rigid_body->inertia : 0.0f;
            }
        }

        void computeCircleMass(std::shared_ptr<entcosy::Entity> entity, float density)
        {

            CircleColliderComponent* collider = entity->get<CircleColliderComponent>();
            RigidBodyComponent* rigid_body = entity->get<RigidBodyComponent>();

            if(rigid_body != nullptr)
            {
                rigid_body->mass = M_PI * collider->radius * collider->radius * density;
                rigid_body->inverse_mass = (rigid_body->mass) ? 100.0f / rigid_body->mass : 0.0f;
                rigid_body->inertia = rigid_body->mass * collider->radius * collider->radius;
                rigid_body->inverse_inertia = (rigid_body->inertia) ? 100.0f / rigid_body->inertia : 0.0f;
            }
        }

        void applyForce( RigidBodyComponent* rigid_body, const Vect2& f )
        {
            rigid_body->force += f;
        }

        void applyImpulse ( RigidBodyComponent* rigid_body, const Vect2& impulse, const Vect2& contactVector )
        {
            rigid_body->velocity += rigid_body->inverse_mass * impulse;
            float result = cross(contactVector, impulse );
            rigid_body->angular_velocity += rigid_body->inverse_inertia * result;
        }

        Vect2 getPolygonSupport( PolygonColliderComponent* collider, const Vect2& dir )
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