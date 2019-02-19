#include <ctime>
#include <iostream>
#include "core/game.hpp"

int main() {
    std::srand(std::time(nullptr)); 
	auto success = EXIT_FAILURE;
    
	// try
	// {
		Game game("Platchamer", 1366, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_ALLOW_HIGHDPI);
		success = game.run();
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cout << "Exception: " << e.what();
	// 	std::cin.get();
	// }
	// catch (...)
	// {
	// 	std::cout << "Threw an unknown exception. Please derive from std::exception.";
	// 	std::cin.get();
	// }

	return success;
}