#ifndef BULLET_SYSTEM_HPP
#define BULLET_SYSTEM_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

class BulletSystem : public entcosy::System
{
public:
    BulletSystem();

	virtual ~BulletSystem();

	virtual void configure(entcosy::Registry* registry) override;

	virtual void unconfigure(entcosy::Registry* registry) override;

	virtual void update(entcosy::Registry* registry, float deltaTime) override;

};

#endif