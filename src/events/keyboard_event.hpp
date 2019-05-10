#ifndef KEYBOARD_EVENT_HPP
#define KEYBOARD_EVENT_HPP

#include <SDL2/SDL_events.h>
#include "../libs/entcosy/src/entcosy/registry.hpp"

struct KeyboardEvent
{

    KeyboardEvent(const SDL_Keycode &keycode) : keycode(keycode) { }

	SDL_Keycode keycode;

    RTTR_ENABLE();
};

#endif
