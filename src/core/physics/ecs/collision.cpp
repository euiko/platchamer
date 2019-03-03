
#include <cstdint>
#include <cassert>
#include "collision.hpp"
#include "rigid_body.hpp"
#include "../../../components/polygon_collider_component.hpp"
#include "../../../types/vect2.hpp"

namespace physics
{
    namespace ecs
    {

        CollisionCallback Dispatch[Collider::ColliderCount][Collider::ColliderCount] =
        {
        {
            CircletoCircle, CircletoPolygon
        },
        {
            PolygontoCircle, PolygontoPolygon
        },
        };

        void CircletoCircle( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b )
        {
            // CircleCollider *A = reinterpret_cast<CircleCollider *>(a->shape);
            // CircleCollider *B = reinterpret_cast<CircleCollider *>(b->shape);

            // // Calculate translational vector, which is normal
            // Vect2 normal = b->position - a->position;

            // float dist_sqr = normal.sqrLength();
            // float radius = A->radius + B->radius;

            // // Not in contact
            // if(dist_sqr >= radius * radius)
            // {
            //     m->contact_count = 0;
            //     return;
            // }

            // float distance = std::sqrt( dist_sqr );

            // m->contact_count = 1;

            // if(distance == 0.0f)
            // {
            //     m->penetration = A->radius;
            //     m->normal = Vect2( 1, 0 );
            //     m->contacts [0] = a->position;
            // }
            // else
            // {
            //     m->penetration = radius - distance;
            //     m->normal = normal / distance; // Faster than using normalized since we already performed sqrt
            //     m->contacts[0] = m->normal * A->radius + a->position;
            // }
        }

        void CircletoPolygon( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b )
        {
            // CircleCollider *A       = reinterpret_cast<CircleCollider *>      (a->shape);
            // PolygonCollider *B = reinterpret_cast<PolygonCollider *>(b->shape);

            // m->contact_count = 0;

            // // Transform circle center to Polygon model space
            // Vect2 center = a->position;
            // center = B->u.transpose( ) * (center - b->position);

            // // Find edge with minimum penetration
            // // Exact concept as using support points in Polygon vs Polygon
            // float separation = -FLT_MAX;
            // uint32_t faceNormal = 0;
            // for(uint32_t i = 0; i < B->m_vertexCount; ++i)
            // {
            //     float s = B->m_normals[i].dot( center - B->m_vertices[i] );

            //     if(s > A->radius)
            //     return;

            //     if(s > separation)
            //     {
            //     separation = s;
            //     faceNormal = i;
            //     }
            // }

            // // Grab face's vertices
            // Vect2 v1 = B->m_vertices[faceNormal];
            // uint32_t i2 = faceNormal + 1 < B->m_vertexCount ? faceNormal + 1 : 0;
            // Vect2 v2 = B->m_vertices[i2];

            // // Check to see if center is within polygon
            // if(separation < EPSILON)
            // {
            //     m->contact_count = 1;
            //     m->normal = -(B->u * B->m_normals[faceNormal]);
            //     m->contacts[0] = m->normal * A->radius + a->position;
            //     m->penetration = A->radius;
            //     return;
            // }

            // // Determine which voronoi region of the edge center of circle lies within
            // float dot1 = dot( center - v1, v2 - v1 );
            // float dot2 = dot( center - v2, v1 - v2 );
            // m->penetration = A->radius - separation;

            // // Closest to v1
            // if(dot1 <= 0.0f)
            // {
            //     if(distSqr( center, v1 ) > A->radius * A->radius)
            //     return;

            //     m->contact_count = 1;
            //     Vect2 n = v1 - center;
            //     n = B->u * n;
            //     n.normalize( );
            //     m->normal = n;
            //     v1 = B->u * v1 + b->position;
            //     m->contacts[0] = v1;
            // }

            // // Closest to v2
            // else if(dot2 <= 0.0f)
            // {
            //     if(distSqr( center, v2 ) > A->radius * A->radius)
            //     return;

            //     m->contact_count = 1;
            //     Vect2 n = v2 - center;
            //     v2 = B->u * v2 + b->position;
            //     m->contacts[0] = v2;
            //     n = B->u * n;
            //     n.normalize( );
            //     m->normal = n;
            // }

            // // Closest to face
            // else
            // {
            //     Vect2 n = B->m_normals[faceNormal];
            //     if(dot( center - v1, n ) > A->radius)
            //     return;

            //     n = B->u * n;
            //     m->normal = -n;
            //     m->contacts[0] = m->normal * A->radius + a->position;
            //     m->contact_count = 1;
            // }
        }

        void PolygontoCircle( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b )
        {
            // CircletoPolygon( m, b, a );
            // m->normal = -m->normal;
        }

        float FindAxisLeastPenetration( uint32_t *faceIndex, ::ecs::Entity *entity_A, ::ecs::Entity *entity_B )
        {
            float bestDistance = -FLT_MAX;
            uint32_t bestIndex;
            
            ::ecs::ComponentHandle<PolygonColliderComponent> polygonColliderA = entity_A->get<PolygonColliderComponent>();
            ::ecs::ComponentHandle<PolygonColliderComponent> polygonColliderB = entity_B->get<PolygonColliderComponent>();
            
            for(uint32_t i = 0; i < polygonColliderA->m_vertexCount; ++i)
            {
                // Retrieve a face normal from A
                Vect2 n = polygonColliderA->m_normals[i];
                Vect2 nw = polygonColliderA->orientation_matrix * n;

                // Transform face normal into B's model space
                Matrix2 buT = polygonColliderB->orientation_matrix.transpose( );
                n = buT * nw;

                // Retrieve support point from B along -n
                Vect2 s =  getPolygonSupport(polygonColliderB, -n);

                // Retrieve vertex on face from A, transform into
                // B's model space
                Vect2 v = polygonColliderA->m_vertices[i];
                v = polygonColliderA->orientation_matrix * v + entity_A->get<PositionComponent>()->pos;
                v -= entity_B->get<PositionComponent>()->pos;
                v = buT * v;

                // Compute penetration distance (in B's model space)
                float d = n.dot( s - v );

                // Store greatest distance
                if(d > bestDistance)
                {
                    bestDistance = d;
                    bestIndex = i;
                }
            }

            *faceIndex = bestIndex;
            return bestDistance;
        }

        void FindIncidentFace( Vect2 *v, ::ecs::Entity *ref_entity, ::ecs::Entity *inc_entity, uint32_t referenceIndex )
        {
            ::ecs::ComponentHandle<PolygonColliderComponent> polygonColliderRef = ref_entity->get<PolygonColliderComponent>();

            ::ecs::ComponentHandle<PolygonColliderComponent> polygonColliderInc = inc_entity->get<PolygonColliderComponent>();
            ::ecs::ComponentHandle<PositionComponent> positionInc = inc_entity->get<PositionComponent>();
            Vect2 referenceNormal = polygonColliderRef->m_normals[referenceIndex];

            // Calculate normal in incident's frame of reference
            referenceNormal = polygonColliderRef->orientation_matrix * referenceNormal; // To world space
            referenceNormal = polygonColliderInc->orientation_matrix.transpose( ) * referenceNormal; // To incident's model space

            // Find most anti-normal face on incident polygon
            int32_t incidentFace = 0;
            float minDot = FLT_MAX;
            for(uint32_t i = 0; i < polygonColliderInc->m_vertexCount; ++i)
            {
                float dot = referenceNormal.dot( polygonColliderInc->m_normals[i] );
                if(dot < minDot)
                {
                minDot = dot;
                incidentFace = i;
                }
            }

            // Assign face vertices for incidentFace
            v[0] = polygonColliderInc->orientation_matrix * polygonColliderInc->m_vertices[incidentFace] + positionInc->pos;
            incidentFace = (incidentFace + 1 >= (int32_t)polygonColliderInc->m_vertexCount) ? 0 : incidentFace + 1;
            v[1] = polygonColliderInc->orientation_matrix * polygonColliderInc->m_vertices[incidentFace] + positionInc->pos;
            }

            int32_t Clip( Vect2 n, float c, Vect2 *face )
            {
            uint32_t sp = 0;
            Vect2 out[2] = {
                face[0],
                face[1]
            };

            // Retrieve distances from each endpoint to the line
            // d = ax + by - c
            float d1 = n.dot( face[0] ) - c;
            float d2 = n.dot( face[1] ) - c;

            // If negative (behind plane) clip
            if(d1 <= 0.0f) out[sp++] = face[0];
            if(d2 <= 0.0f) out[sp++] = face[1];
            
            // If the points are on different sides of the plane
            if(d1 * d2 < 0.0f) // less than to ignore -0.0f
            {
                // Push interesection point
                float alpha = d1 / (d1 - d2);
                out[sp] = face[0] + alpha * (face[1] - face[0]);
                ++sp;
            }

            // Assign our new converted values
            face[0] = out[0];
            face[1] = out[1];

            assert( sp != 3 );

            return sp;
        }

        void PolygontoPolygon( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b )
        {
            ::ecs::ComponentHandle<PolygonColliderComponent> A = a->get<PolygonColliderComponent>();
            ::ecs::ComponentHandle<PolygonColliderComponent> B = b->get<PolygonColliderComponent>();
            m->contact_count = 0;

            // Check for a separating axis with A's face planes
            uint32_t faceA; 
            float penetrationA = FindAxisLeastPenetration( &faceA, a, b );
            if(penetrationA >= 0.0f)
                return;

            // Check for a separating axis with B's face planes
            uint32_t faceB;
            float penetrationB = FindAxisLeastPenetration( &faceB, b, a );
            if(penetrationB >= 0.0f)
                return;

            uint32_t referenceIndex;
            bool flip; // Always point from a to b

            ::ecs::Entity *refEntity; // Reference
            ::ecs::Entity *incEntity; // Incident

            // Determine which ColliderShape contains reference face
            if(biasGreaterThan( penetrationA, penetrationB ))
            {
                refEntity = a;
                incEntity = b;
                referenceIndex = faceA;
                flip = false;
            }

            else
            {
                refEntity = b;
                incEntity = a;
                referenceIndex = faceB;
                flip = true;
            }

            // World space incident face
            Vect2 incidentFace[2];
            FindIncidentFace( incidentFace, refEntity, incEntity, referenceIndex );

            //        y
            //        ^  ->n       ^
            //      +---c ------posPlane--
            //  x < | i |\
            //      +---+ c-----negPlane--
            //             \       v
            //              r
            //
            //  r : reference face
            //  i : incident poly
            //  c : clipped point
            //  n : incident normal


            ::ecs::ComponentHandle<PolygonColliderComponent> polygonColliderRef = refEntity->get<PolygonColliderComponent>();
            ::ecs::ComponentHandle<PositionComponent> positionRef = refEntity->get<PositionComponent>();

            // Setup reference face vertices
            Vect2 v1 = polygonColliderRef->m_vertices[referenceIndex];
            referenceIndex = referenceIndex + 1 == polygonColliderRef->m_vertexCount ? 0 : referenceIndex + 1;
            Vect2 v2 = polygonColliderRef->m_vertices[referenceIndex];

            // Transform vertices to world space
            v1 = polygonColliderRef->orientation_matrix * v1 + positionRef->pos;
            v2 = polygonColliderRef->orientation_matrix * v2 + positionRef->pos;

            // Calculate reference face side normal in world space
            Vect2 sidePlaneNormal = (v2 - v1);
            sidePlaneNormal.normalize( );

            // Orthogonalize
            Vect2 refFaceNormal( sidePlaneNormal.y, -sidePlaneNormal.x );

            // ax + by = c
            // c is distance from origin
            float refC = refFaceNormal.dot( v1 );
            float negSide = -(sidePlaneNormal.dot( v1 ));
            float posSide =  sidePlaneNormal.dot( v2 );

            // Clip incident face to reference face side planes
            if(Clip( -sidePlaneNormal, negSide, incidentFace ) < 2)
                return; // Due to floating point error, possible to not have required points

            if(Clip(  sidePlaneNormal, posSide, incidentFace ) < 2)
                return; // Due to floating point error, possible to not have required points

            // Flip
            m->normal = flip ? -refFaceNormal : refFaceNormal;

            // Keep points behind reference face
            uint32_t cp = 0; // clipped points behind reference face
            float separation = refFaceNormal.dot( incidentFace[0] ) - refC;
            if(separation <= 0.0f)
            {
                m->contacts[cp] = incidentFace[0];
                m->penetration = -separation;
                ++cp;
            }
            else
                m->penetration = 0;

            separation = refFaceNormal.dot( incidentFace[1] ) - refC;
            if(separation <= 0.0f)
            {
                m->contacts[cp] = incidentFace[1];

                m->penetration += -separation;
                ++cp;

                // Average penetration
                m->penetration /= (float)cp;
            }

            m->contact_count = cp;
        }

    }
}