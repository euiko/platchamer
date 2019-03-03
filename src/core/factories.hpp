#ifndef CORE_FACTORIES_HPP
#define CORE_FACTORIES_HPP

#include "ecs/registry.hpp"

ecs::Entity* makePlayer(ecs::Registry* registry);

ecs::Entity* makeBullet(ecs::Registry* registry, ecs::Entity* player);


#endif