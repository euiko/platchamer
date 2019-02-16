#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include "../graphics/window.hpp"
#include "../core/ecs/registry.hpp"

class Game
{
public:
    Game(const std::string& title, int w, int h, Uint32 flags);
    ~Game() = default;
    int run();

private:
    void event();
    void update(double time);
    void render();

private:
    Window m_window;
    ecs::Registry* m_registry;
};

#endif