#ifndef BULLET_SYSTEM_HPP
#define BULLET_SYSTEM_HPP

#include "../core/ecs.hpp"

using namespace ecs;
class BulletSystem : public EntitySystem
{
public:
    BulletSystem();

	virtual ~BulletSystem();

	virtual void configure(Registry* registry) override;

	virtual void unconfigure(Registry* registry) override;

	virtual void tick(Registry* registry, float deltaTime) override;

};

#endif