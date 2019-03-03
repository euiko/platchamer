#ifndef POLYGON_COLLIDER_COMPONENT_HPP
#define POLYGON_COLLIDER_COMPONENT_HPP

#include <stdint.h>
#include <vector>
#include "../types/vect2.hpp"
#include "../types/matrix2.hpp"
#include "../types/collider.hpp"
#include "../core/ecs/registry.hpp"

#ifndef MaxPolyVertexCount
#define MaxPolyVertexCount 64
#endif

struct PolygonColliderComponent : Collider
{

    PolygonColliderComponent(
        const uint32_t& _vertex_count, const std::vector<Vect2>& _vertices,
        const std::vector<Vect2>& _normals, const Matrix2& _orientation_matrix
    ) : Collider({PolygonCollider}), m_vertexCount(_vertex_count), m_vertices(_vertices)
        , m_normals(_normals), orientation_matrix(_orientation_matrix)
    {
    }

    ECS_DECLARE_TYPE;

    uint32_t m_vertexCount;
    std::vector<Vect2> m_vertices;
    std::vector<Vect2> m_normals;

    Matrix2 orientation_matrix;

};

#endif