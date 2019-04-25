#include <ctime>
#include <iostream>
#include "core/game.hpp"

int main() {
    
	Game game("Platchamer", 1366, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_ALLOW_HIGHDPI);
	game.run();

	return 0;
}