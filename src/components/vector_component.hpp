#ifndef VECTOR_COMPONENT_HPP
#define VECTOR_COMPONENT_HPP

#include <vector>
#include "../core/ecs/registry.hpp"

struct VectorComponent
{
    ECS_DECLARE_TYPE;
    VectorComponent(std::vector<float> points): points(points)
    {
    }

    std::vector<float> points;
};

ECS_DEFINE_TYPE(VectorComponent);

#endif