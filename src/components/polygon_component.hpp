#ifndef VECTOR_COMPONENT_HPP
#define VECTOR_COMPONENT_HPP

#include <vector>
#include "../core/ecs/registry.hpp"
#include "../types/vect2.hpp"

struct PolygonComponent
{
    ECS_DECLARE_TYPE;
    PolygonComponent(std::vector<Vect2> points): points(points)
    {
    }

    std::vector<Vect2> points;
    Vect2 centroid;
};

#endif