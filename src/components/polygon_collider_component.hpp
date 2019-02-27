#ifndef POLYGON_COLLIDER_COMPONENT_HPP
#define POLYGON_COLLIDER_COMPONENT_HPP

#include "../types/vect2.hpp"
#include "../core/ecs/registry.hpp"
#include <stdint.h>

#ifndef MaxPolyVertexCount
#define MaxPolyVertexCount 64
#endif

struct PolygonColliderComponent
{

    ECS_DECLARE_TYPE;

    uint32_t m_vertexCount;
    Vect2 m_vertices[MaxPolyVertexCount];
    Vect2 m_normals[MaxPolyVertexCount];

};

#endif