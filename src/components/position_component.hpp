#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

#include "../types/vect2.hpp"
#include "../libs/entcosy/src/entcosy/registry.hpp"

struct PositionComponent 
{
    ECS_DECLARE_TYPE;
    
    PositionComponent(float x, float y, float rotation = 0) : pos(x, y), rotation(rotation)
    {
    }

    Vect2 pos;
    float rotation;
};


#endif