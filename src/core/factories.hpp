#ifndef CORE_FACTORIES_HPP
#define CORE_FACTORIES_HPP

#include "ecs/registry.hpp"
#include "../types/vect2.hpp"
#include "../components/position_component.hpp"
#include "../components/polygon_component.hpp"
#include "../tags/player_tag.hpp"
#include "../tags/bullet_tag.hpp"

ecs::Entity* makePlayer(ecs::Registry* registry);

ecs::Entity* makeBullet(ecs::Registry* registry, ecs::Entity* player);


#endif