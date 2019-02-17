#ifndef VECTOR_COMPONENT_HPP
#define VECTOR_COMPONENT_HPP

#include <vector>
#include "../core/ecs/registry.hpp"
#include "../types/vect2.hpp"

struct VectorComponent
{
    ECS_DECLARE_TYPE;
    VectorComponent(std::vector<Vect2> points): points(points)
    {
    }

    std::vector<Vect2> points;
};

#endif