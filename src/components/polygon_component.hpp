#ifndef VECTOR_COMPONENT_HPP
#define VECTOR_COMPONENT_HPP

#include <vector>
#include "../core/ecs/registry.hpp"
#include "../types/vect2.hpp"

struct PolygonComponent
{
    ECS_DECLARE_TYPE;
    PolygonComponent(std::vector<Vect2> points, uint32_t color = 0xFF999999, float scale = 1.0f)
        : points(points), color(color), scale(scale)
    {
    }

    std::vector<Vect2> points;
    Vect2 centroid;
    float scale;
    uint32_t color;
};

#endif