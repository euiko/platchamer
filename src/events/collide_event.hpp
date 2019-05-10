#ifndef COLLIDE_EVENT_HPP
#define COLLIDE_EVENT_HPP

// #include <SDL2/SDL_events.h>
#include "../libs/entcosy/src/entcosy/registry.hpp"

struct CollideEvent
{
	std::shared_ptr<entcosy::Entity> entityA, entityB;
	bool isCollide;

    CollideEvent(std::shared_ptr<entcosy::Entity> entity_a, std::shared_ptr<entcosy::Entity> entity_b, bool is_collide)
        : entityA(entity_a), entityB(entity_b), isCollide(is_collide) { }

    RTTR_ENABLE();
};

#endif
