#ifndef BULLET_SYSTEM_HPP
#define BULLET_SYSTEM_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

class BulletSystem : public entcosy::System
{
public:
    BulletSystem();

	virtual ~BulletSystem();

	virtual void configure(std::shared_ptr<entcosy::Registry> registry) override;

	virtual void unconfigure(std::shared_ptr<entcosy::Registry> registry) override;

	virtual void update(std::shared_ptr<entcosy::Registry> registry, float deltaTime) override;

};

#endif
