#ifndef CORE_FACTORIES_HPP
#define CORE_FACTORIES_HPP

#include "ecs/registry.hpp"

ecs::Entity* makePlayer(ecs::Registry* registry, float x = 0.0f, float y = 0.0f);

ecs::Entity* makeBullet(ecs::Registry* registry, ecs::Entity* player);

ecs::Entity* makeBlock(ecs::Registry* registry, float x, float y, float rotation = 0.0f);

ecs::Entity* makeEnemy(ecs::Registry* registry, float x, float y);

#endif