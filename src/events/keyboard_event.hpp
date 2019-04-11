#ifndef KEYBOARD_EVENT_HPP
#define KEYBOARD_EVENT_HPP

#include <SDL2/SDL_events.h>
#include "../libs/entcosy/src/entcosy/registry.hpp"

struct KeyboardEvent
{
	ENTCOSY_DECLARE_TYPE;

	SDL_Keycode keycode;
};

#endif