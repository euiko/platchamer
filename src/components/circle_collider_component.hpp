#ifndef CIRCLE_COLLDIER_COMPONENT_HPP
#define CIRCLE_COLLDIER_COMPONENT_HPP

#include "../types/collider.hpp"
#include "../libs/entcosy/src/entcosy/registry.hpp"

struct CircleColliderComponent : Collider
{
    ENTCOSY_DECLARE_TYPE;

    CircleColliderComponent(const float& radius) 
        : Collider({CircleCollider, 0.0f}), radius(radius)
    {
    }

    float radius;
};

#endif