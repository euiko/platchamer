#ifndef PLAYER_CONTROL_SYSTEM_HPP
#define PLAYER_CONTROL_SYSTEM_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"
#include "../events/keyboard_event.hpp"

class PlayerControlSystem : public entcosy::System,
public entcosy::EventSubscriber<KeyboardEvent>
{
public:
	virtual ~PlayerControlSystem();

	virtual void configure(entcosy::Registry* registry) override;

	virtual void unconfigure(entcosy::Registry* registry) override;

	virtual void update(entcosy::Registry* registry, float deltaTime) override;

    virtual void receive(entcosy::Registry* world, const KeyboardEvent& event) override;
};

#endif