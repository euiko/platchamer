#ifndef POLYGON_COLLIDER_HPP
#define POLYGON_COLLIDER_HPP

#include <cassert>
#include <algorithm>
#include <cfloat>
#include "collider_shape.hpp"
#include "../rigid_body.hpp"
#include "../../../types/vect2.hpp"

#ifndef MaxPolyVertexCount
#define MaxPolyVertexCount 64
#endif

struct PolygonCollider : public ColliderShape
{

    ColliderShape *Clone( void ) const
    {
        PolygonCollider *poly = new PolygonCollider( );
        poly->u = u;
        for(uint32_t i = 0; i < m_vertexCount; ++i)
        {
        poly->m_vertices[i] = m_vertices[i];
        poly->m_normals[i] = m_normals[i];
        }
        poly->m_vertexCount = m_vertexCount;
        return poly;
    }

    void initialize( void )
    {
        computeMass( 1.0f );
    }

    void computeMass( float density )
    {
        // Calculate centroid and moment of interia
        Vect2 c( 0.0f, 0.0f ); // centroid
        float area = 0.0f;
        float I = 0.0f;
        const float k_inv3 = 1.0f / 3.0f;

        for(uint32_t i1 = 0; i1 < m_vertexCount; ++i1)
        {
            Vect2 p1( m_vertices[i1] );
            uint32_t i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
            Vect2 p2( m_vertices[i2] );

            float D = p1.cross(p2);
            float triangleArea = 0.5f * D;

            area += triangleArea;

            c += triangleArea * k_inv3 * (p1 + p2);

            float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
            float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
            I += (0.25f * k_inv3 * D) * (intx2 + inty2);
        }

        c *= 1.0f / area;

        for(uint32_t i = 0; i < m_vertexCount; ++i)
            m_vertices[i] -= c;

        body->m = density * area;
        body->im = (body->m) ? 1.0f / body->m : 0.0f;
        body->I = I * density;
        body->iI = body->I ? 1.0f / body->I : 0.0f;
    }

    void setOrient( float radians )
    {
        u = { radians };
    }
    // Half width and half height
    void setBox( float hw, float hh )
    {
        m_vertexCount = 4;
        m_vertices[0] = { -hw, -hh };
        m_vertices[1] = { hw, -hh };
        m_vertices[2] = { hw,  hh };
        m_vertices[3] = { hw,  hh };
        m_normals[0] = { 0.0f,  -1.0f };
        m_normals[1] = { 1.0f,   0.0f };
        m_normals[2] = { 0.0f,   1.0f };
        m_normals[3] = { 1.0f,   0.0f };
    }

    void set( Vect2 *vertices, uint32_t count )
    {
        // No hulls with less than 3 vertices (ensure actual polygon)
        assert( count > 2 && count <= MaxPolyVertexCount );
        count = std::min( (int32_t)count, MaxPolyVertexCount );

        // Find the right most point on the hull
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

        // If matching x then take farthest negative y
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

            // Search for next index that wraps around the hull
            // by computing cross products to find the most counter-clockwise
            // vertex in the set, given the previos hull index
            int32_t nextHullIndex = 0;
            for(int32_t i = 1; i < (int32_t)count; ++i)
            {
                // Skip if same coordinate as we need three unique
                // points in the set to perform a cross product
                if(nextHullIndex == indexHull)
                {
                nextHullIndex = i;
                continue;
                }

                // Cross every set of three unique vertices
                // Record each counter clockwise third vertex and add
                // to the output hull
                // See : http://www.oocities.org/pcgpe/math2d.html
                Vect2 e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
                Vect2 e2 = vertices[i] - vertices[hull[outCount]];
                float c = e1.cross(e2);
                if(c < 0.0f)
                    nextHullIndex = i;

                // Cross product is zero then e vectors are on same line
                // therefor want to record vertex farthest along that line
                if(c == 0.0f && e2.sqrLength( ) > e1.sqrLength( ))
                    nextHullIndex = i;
            }
            
            ++outCount;
            indexHull = nextHullIndex;

            // Conclude algorithm upon wrap-around
            if(nextHullIndex == rightMost)
            {
                m_vertexCount = outCount;
                break;
            }
        }

        // Copy vertices into shape's vertices
        for(uint32_t i = 0; i < m_vertexCount; ++i)
            m_vertices[i] = vertices[hull[i]];

        // Compute face normals
        for(uint32_t i1 = 0; i1 < m_vertexCount; ++i1)
        {
            uint32_t i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
            Vect2 face = m_vertices[i2] - m_vertices[i1];

            // Ensure no zero-length edges, because that's bad
            assert( face.sqrLength( ) > EPSILON * EPSILON );

            // Calculate normal with 2D cross product between vector and scalar
            m_normals[i1] = Vect2( face.y, -face.x );
            m_normals[i1].normalize( );
        }
    }

    // The extreme point along a direction within a polygon
    Vect2 GetSupport( const Vect2& dir )
    {
        float bestProjection = -FLT_MAX;
        Vect2 bestVertex;

        for(uint32_t i = 0; i < m_vertexCount; ++i)
        {
        Vect2 v = m_vertices[i];
        float projection = v.dot(dir);

        if(projection > bestProjection)
        {
            bestVertex = v;
            bestProjection = projection;
        }
        }

        return bestVertex;
    }

    Type getType( void ) const
    {
        return colliderPoly;
    }

    uint32_t m_vertexCount;
    Vect2 m_vertices[MaxPolyVertexCount];
    Vect2 m_normals[MaxPolyVertexCount];
};

#endif