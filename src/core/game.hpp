#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include "../graphics/window.hpp"
#include "../core/ecs/registry.hpp"
#include "../systems/renderer_system.hpp"

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
    std::unique_ptr<ecs::Registry> m_registry;
    RendererSystem m_renderer_system;
};

#endif