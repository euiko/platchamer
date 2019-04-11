#ifndef CORE_FACTORIES_HPP
#define CORE_FACTORIES_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

std::shared_ptr<entcosy::Entity> makePlayer(entcosy::Registry* registry, float x = 0.0f, float y = 0.0f);

std::shared_ptr<entcosy::Entity> makeBullet(entcosy::Registry* registry, std::shared_ptr<entcosy::Entity> player);

std::shared_ptr<entcosy::Entity> makeBlock(entcosy::Registry* registry, float x, float y, float rotation = 0.0f);

std::shared_ptr<entcosy::Entity> makeEnemy(entcosy::Registry* registry, float x, float y);

ecs::Entity* makeCamera(ecs::Registry* registry, ecs::Entity* looked_object);

#endif