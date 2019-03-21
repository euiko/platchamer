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

    PolygonColliderComponent(const std::vector<Vect2>& _vertices) 
        : Collider({PolygonCollider, 0.0f}), m_vertexCount(_vertices.size()), m_vertices(_vertices)
    {
    }

    ECS_DECLARE_TYPE;

    uint32_t m_vertexCount;
    std::vector<Vect2> m_vertices;
    std::vector<Vect2> m_normals;

};

#endif