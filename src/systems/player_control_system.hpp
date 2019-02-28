#ifndef PLAYER_CONTROL_SYSTEM_HPP
#define PLAYER_CONTROL_SYSTEM_HPP

#include "../core/ecs/registry.hpp"
#include "../events/keyboard_event.hpp"

using namespace ecs;
class PlayerControlSystem : public EntitySystem,
public EventSubscriber<KeyboardEvent>
{
public:
	virtual ~PlayerControlSystem();

	virtual void configure(Registry* registry) override;

	virtual void unconfigure(Registry* registry) override;

	virtual void tick(Registry* registry, float deltaTime) override;

    virtual void receive(Registry* world, const KeyboardEvent& event) override;
};

#endif