
#include <cstdint>
#include <cassert>
#include "collision.hpp"
#include "rigid_body.hpp"
#include "../../../components/polygon_collider_component.hpp"
#include "../../../components/circle_collider_component.hpp"
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
            ::ecs::ComponentHandle<CircleColliderComponent> A = a->get<CircleColliderComponent>();
            ::ecs::ComponentHandle<CircleColliderComponent> B = b->get<CircleColliderComponent>();

            ::ecs::ComponentHandle<PositionComponent> positionA = a->get<PositionComponent>();
            ::ecs::ComponentHandle<PositionComponent> positionB = b->get<PositionComponent>();

            Vect2 normal = positionA->pos - positionB->pos;

            float dist_sqr = normal.sqrLength();
            float radius = A->radius + B->radius;

            if(dist_sqr >= radius * radius)
            {
                m->contact_count = 0;
                return;
            }

            float distance = std::sqrt( dist_sqr );

            m->contact_count = 1;

            if(distance == 0.0f)
            {
                m->penetration = A->radius;
                m->normal = Vect2( 1, 0 );
                m->contacts [0] = positionA->pos;
            }
            else
            {
                m->penetration = radius - distance;
                m->normal = normal / distance; 
                m->contacts[0] = m->normal * A->radius + positionA->pos;
            }
        }

        void CircletoPolygon( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b )
        {
            ::ecs::ComponentHandle<CircleColliderComponent> A = a->get<CircleColliderComponent>();
            ::ecs::ComponentHandle<PolygonColliderComponent> B = b->get<PolygonColliderComponent>();

            ::ecs::ComponentHandle<PositionComponent> positionA = a->get<PositionComponent>();
            ::ecs::ComponentHandle<PositionComponent> positionB = b->get<PositionComponent>();

            m->contact_count = 0;

            Vect2 center = positionA->pos;
            center = B->orientation_matrix.transpose( ) * (center - positionB->pos);

            float separation = -FLT_MAX;
            uint32_t faceNormal = 0;
            for(uint32_t i = 0; i < B->m_vertexCount; ++i)
            {
                float s = B->m_normals[i].dot( center - B->m_vertices[i] );

                if(s > A->radius)
                return;

                if(s > separation)
                {
                separation = s;
                faceNormal = i;
                }
            }

            Vect2 v1 = B->m_vertices[faceNormal];
            uint32_t i2 = faceNormal + 1 < B->m_vertexCount ? faceNormal + 1 : 0;
            Vect2 v2 = B->m_vertices[i2];

            if(separation < EPSILON)
            {
                m->contact_count = 1;
                m->normal = -(B->orientation_matrix * B->m_normals[faceNormal]);
                m->contacts[0] = m->normal * A->radius + positionA->pos;
                m->penetration = A->radius;
                return;
            }

            float dot1 = dot( center - v1, v2 - v1 );
            float dot2 = dot( center - v2, v1 - v2 );
            m->penetration = A->radius - separation;

            if(dot1 <= 0.0f)
            {
                if(distSqr( center, v1 ) > A->radius * A->radius)
                return;

                m->contact_count = 1;
                Vect2 n = v1 - center;
                n = B->orientation_matrix * n;
                n.normalize( );
                m->normal = n;
                v1 = B->orientation_matrix * v1 + positionB->pos;
                m->contacts[0] = v1;
            }

            else if(dot2 <= 0.0f)
            {
                if(distSqr( center, v2 ) > A->radius * A->radius)
                return;

                m->contact_count = 1;
                Vect2 n = v2 - center;
                v2 = B->orientation_matrix * v2 + positionB->pos;
                m->contacts[0] = v2;
                n = B->orientation_matrix * n;
                n.normalize( );
                m->normal = n;
            }
            else
            {
                Vect2 n = B->m_normals[faceNormal];
                if(dot( center - v1, n ) > A->radius)
                return;

                n = B->orientation_matrix * n;
                m->normal = -n;
                m->contacts[0] = m->normal * A->radius + positionA->pos;
                m->contact_count = 1;
            }
        }

        void PolygontoCircle( Manifold *m, ::ecs::Entity *a, ::ecs::Entity *b )
        {
            CircletoPolygon( m, b, a );
            m->normal = -m->normal;
        }

        float FindAxisLeastPenetration( uint32_t *faceIndex, ::ecs::Entity *entity_A, ::ecs::Entity *entity_B )
        {
            float bestDistance = -FLT_MAX;
            uint32_t bestIndex;
            
            ::ecs::ComponentHandle<PolygonColliderComponent> polygonColliderA = entity_A->get<PolygonColliderComponent>();
            ::ecs::ComponentHandle<PolygonColliderComponent> polygonColliderB = entity_B->get<PolygonColliderComponent>();
            
            for(uint32_t i = 0; i < polygonColliderA->m_vertexCount; ++i)
            {
                Vect2 n = polygonColliderA->m_normals[i];
                Vect2 nw = polygonColliderA->orientation_matrix * n;

                Matrix2 buT = polygonColliderB->orientation_matrix.transpose( );
                n = buT * nw;

                Vect2 s = getPolygonSupport(polygonColliderB, -n);

                Vect2 v = polygonColliderA->m_vertices[i];
                v = polygonColliderA->orientation_matrix * v + entity_A->get<PositionComponent>()->pos;
                v -= entity_B->get<PositionComponent>()->pos;
                v = buT * v;
                float d = n.dot( s - v );
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

            referenceNormal = polygonColliderRef->orientation_matrix * referenceNormal;
            referenceNormal = polygonColliderInc->orientation_matrix.transpose( ) * referenceNormal;

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

            float d1 = n.dot( face[0] ) - c;
            float d2 = n.dot( face[1] ) - c;

            if(d1 <= 0.0f) out[sp++] = face[0];
            if(d2 <= 0.0f) out[sp++] = face[1];
            if(d1 * d2 < 0.0f)
            {
                float alpha = d1 / (d1 - d2);
                out[sp] = face[0] + alpha * (face[1] - face[0]);
                ++sp;
            }
            
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

            uint32_t faceA; 
            float penetrationA = FindAxisLeastPenetration( &faceA, a, b );
            if(penetrationA >= 0.0f)
                return;

            uint32_t faceB;
            float penetrationB = FindAxisLeastPenetration( &faceB, b, a );
            if(penetrationB >= 0.0f)
                return;

            uint32_t referenceIndex;
            bool flip;

            ::ecs::Entity *refEntity; // Reference
            ::ecs::Entity *incEntity; // Incident

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

            Vect2 incidentFace[2];
            FindIncidentFace( incidentFace, refEntity, incEntity, referenceIndex );

            ::ecs::ComponentHandle<PolygonColliderComponent> polygonColliderRef = refEntity->get<PolygonColliderComponent>();
            ::ecs::ComponentHandle<PositionComponent> positionRef = refEntity->get<PositionComponent>();

            Vect2 v1 = polygonColliderRef->m_vertices[referenceIndex];
            referenceIndex = referenceIndex + 1 == polygonColliderRef->m_vertexCount ? 0 : referenceIndex + 1;
            Vect2 v2 = polygonColliderRef->m_vertices[referenceIndex];

            v1 = polygonColliderRef->orientation_matrix * v1 + positionRef->pos;
            v2 = polygonColliderRef->orientation_matrix * v2 + positionRef->pos;

            Vect2 sidePlaneNormal = (v2 - v1);
            sidePlaneNormal.normalize( );

            Vect2 refFaceNormal( sidePlaneNormal.y, -sidePlaneNormal.x );

            float refC = refFaceNormal.dot( v1 );
            float negSide = -(sidePlaneNormal.dot( v1 ));
            float posSide =  sidePlaneNormal.dot( v2 );

            if(Clip( -sidePlaneNormal, negSide, incidentFace ) < 2)
                return;
            if(Clip(  sidePlaneNormal, posSide, incidentFace ) < 2)
                return;
            m->normal = flip ? -refFaceNormal : refFaceNormal;

            uint32_t cp = 0;
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

                m->penetration /= (float)cp;
            }

            m->contact_count = cp;
        }

    }
}