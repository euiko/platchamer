#ifndef KEYBOARD_EVENT_HPP
#define KEYBOARD_EVENT_HPP

#include <SDL2/SDL_events.h>
#include "../core/ecs/registry.hpp"

struct KeyboardEvent
{
	ECS_DECLARE_TYPE;

	SDL_Keycode keycode;
};

#endif