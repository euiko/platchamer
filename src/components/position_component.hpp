#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

#include "../types/vect2.hpp"
#include "../core/ecs/registry.hpp"

struct PositionComponent 
{
    ECS_DECLARE_TYPE;
    
    PositionComponent(float x, float y) : pos(x, y)
    {
    }

    Vect2 pos;
};


#endif