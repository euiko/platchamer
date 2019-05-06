#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

#include "../types/vect2.hpp"
#include "../libs/entcosy/src/entcosy/registry.hpp"

struct PositionComponent
{
    ENTCOSY_DECLARE_TYPE;

    PositionComponent() : pos({0, 0}), rotation(0.0f) {}

    PositionComponent(float x, float y, float rotation = 0) : pos(x, y), rotation(rotation)
    {
    }

    Vect2 pos;
    float rotation;

    template<class Archive>
    void serialize(Archive &ar)
    {
        ar(pos, rotation);
    }
};


#endif
