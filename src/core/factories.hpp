#ifndef CORE_FACTORIES_HPP
#define CORE_FACTORIES_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

std::shared_ptr<entcosy::Entity> makePlayer(std::shared_ptr<entcosy::Registry> registry, float x = 0.0f, float y = 0.0f);

std::shared_ptr<entcosy::Entity> makeBullet(std::shared_ptr<entcosy::Registry> registry, std::shared_ptr<entcosy::Entity> player);

std::shared_ptr<entcosy::Entity> makeBlock(std::shared_ptr<entcosy::Registry> registry, float x, float y, float rotation = 0.0f);

std::shared_ptr<entcosy::Entity> makeEnemy(std::shared_ptr<entcosy::Registry> registry, float x, float y);

std::shared_ptr<entcosy::Entity> makeThorn(std::shared_ptr<entcosy::Registry> registry, float x, float y);

std::shared_ptr<entcosy::Entity> makeCamera(std::shared_ptr<entcosy::Registry> registry, std::shared_ptr<entcosy::Entity> looked_object);

#endif
