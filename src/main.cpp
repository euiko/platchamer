#define STB_IMAGE_IMPLEMENTATION
// #define STB_RECT_PACK_IMPLEMENTATION
// #define STB_TRUETYPE_IMPLEMENTATION
// #define STB_TEXTEDIT_IMPLEMENTATION


#include <ctime>
#include <iostream>
#include "core/game.hpp"

LevelManager Game::level_manager;

int main() {

	Game game("Platchamer", 1366, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS
        | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	game.run();

	return 0;
}
