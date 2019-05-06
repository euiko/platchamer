#ifndef CIRCLE_COMPONENT_HPP
#define CIRCLE_COMPONENT_HPP

#include <vector>
#include "../libs/entcosy/src/entcosy/registry.hpp"
#include "../types/vect2.hpp"

struct CircleComponent
{
    ENTCOSY_DECLARE_TYPE;
    CircleComponent() : radius(0.0f), scale(0.0f), color(0xFF000000) {}
    CircleComponent(const float& radius, uint32_t color = 0xFF999999, float scale = 1.0f)
        : radius(radius), color(color), scale(scale)
    {
    }

    float radius;
    float scale;
    uint32_t color;

    template<class Archive>
    void serialize(Archive &ar)
    {
        ar(radius, scale, color);
    }
};

#endif
