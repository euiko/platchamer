#ifndef POLYGON_COLLIDER_COMPONENT_HPP
#define POLYGON_COLLIDER_COMPONENT_HPP

#include <stdint.h>
#include <cereal/types/vector.hpp>
#include "../types/vect2.hpp"
#include "../types/matrix2.hpp"
#include "../types/collider.hpp"
#include "../libs/entcosy/src/entcosy/registry.hpp"

#ifndef MaxPolyVertexCount
#define MaxPolyVertexCount 64
#endif

struct PolygonColliderComponent : public Collider
{

    PolygonColliderComponent() : m_vertexCount(0) {}

    PolygonColliderComponent(const std::vector<Vect2>& _vertices)
        : Collider({PolygonCollider, 0.0f}), m_vertexCount(_vertices.size()), m_vertices(_vertices)
    {
    }

    ENTCOSY_DECLARE_TYPE;

    uint32_t m_vertexCount;
    std::vector<Vect2> m_vertices;
    std::vector<Vect2> m_normals;

    template<class Archive>
    void serialize(Archive &ar)
    {
        ar(cereal::base_class<Collider>( this ), m_vertexCount, m_vertices, m_normals);
    }
};

#endif
