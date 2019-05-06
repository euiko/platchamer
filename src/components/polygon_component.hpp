#ifndef VECTOR_COMPONENT_HPP
#define VECTOR_COMPONENT_HPP

#include <cereal/types/vector.hpp>
#include "../libs/entcosy/src/entcosy/registry.hpp"
#include "../types/vect2.hpp"

struct PolygonComponent
{
    ENTCOSY_DECLARE_TYPE;

    PolygonComponent() : centroid({0,0}), scale(1.0f), color(0xFF999999) {}

    PolygonComponent(std::vector<Vect2> points, uint32_t color = 0xFF999999, float scale = 1.0f)
        : points(points), color(color), scale(scale)
    {
    }

    std::vector<Vect2> points;
    Vect2 centroid;
    float scale;
    uint32_t color;

    template<class Archive>
    void serialize(Archive &ar)
    {
        ar(points, centroid, scale, color);
    }
};

#endif
