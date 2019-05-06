#ifndef PLAYER_CONTROL_SYSTEM_HPP
#define PLAYER_CONTROL_SYSTEM_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"
#include "../events/keyboard_event.hpp"
#include "../events/collide_event.hpp"
#include "../events/reset_player_state_event.hpp"

class PlayerControlSystem : public entcosy::System,
public entcosy::EventSubscriber<KeyboardEvent>,
public entcosy::EventSubscriber<CollideEvent>,
public entcosy::EventSubscriber<ResetPlayerStateEvent>
{
public:
	virtual ~PlayerControlSystem();

	virtual void configure(std::shared_ptr<entcosy::Registry> registry) override;

	virtual void unconfigure(std::shared_ptr<entcosy::Registry> registry) override;

	virtual void update(std::shared_ptr<entcosy::Registry> registry, float deltaTime) override;

    virtual void receive(std::shared_ptr<entcosy::Registry> registry, const KeyboardEvent& event) override;
    virtual void receive(std::shared_ptr<entcosy::Registry> registry, const CollideEvent& event) override;
    virtual void receive(std::shared_ptr<entcosy::Registry> registry, const ResetPlayerStateEvent& event) override;
};

#endif
