#ifndef PLATCHAMER_TYPE_COLLIDERENTITY_HPP
#define PLATCHAMER_TYPE_COLLIDERENTITY_HPP

#include "collider.hpp"
#include "../core/ecs/registry.hpp"

struct ColliderEntity
{
    ecs::Entity* entity;
    Collider* collider;
};


#endif