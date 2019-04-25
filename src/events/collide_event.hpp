#ifndef COLLIDE_EVENT_HPP
#define COLLIDE_EVENT_HPP

// #include <SDL2/SDL_events.h>
#include "../libs/entcosy/src/entcosy/registry.hpp"

struct CollideEvent
{
	ENTCOSY_DECLARE_TYPE;

	std::shared_ptr<entcosy::Entity> entityA, entityB;
	bool isCollide;
};

#endif