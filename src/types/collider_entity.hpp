#ifndef PLATCHAMER_TYPE_COLLIDERENTITY_HPP
#define PLATCHAMER_TYPE_COLLIDERENTITY_HPP

#include "collider.hpp"
#include "../libs/entcosy/src/entcosy/registry.hpp"

struct ColliderEntity
{
    ecs::Entity* entity;
    Collider* collider;
};


#endif