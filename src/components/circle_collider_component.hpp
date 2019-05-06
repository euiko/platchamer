#ifndef CIRCLE_COLLDIER_COMPONENT_HPP
#define CIRCLE_COLLDIER_COMPONENT_HPP

#include "../types/collider.hpp"
#include "../libs/entcosy/src/entcosy/registry.hpp"

struct CircleColliderComponent : public Collider
{
    ENTCOSY_DECLARE_TYPE;

    CircleColliderComponent() : radius(0) { }

    CircleColliderComponent(const float& radius)
        : Collider({CircleCollider, 0.0f}), radius(radius)
    {
    }

    float radius;

    template<class Archive>
    void serialize(Archive &ar)
    {
        ar(cereal::base_class<Collider>( this ), radius);
    }
};

#endif
