#ifndef GAME_HPP
#define GAME_HPP

#define MaxPolyVertexCount 64

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include "../graphics/window.hpp"
#include "../core/ecs.hpp"
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
    platchamer::graphics::Window m_window;
    ecs::Registry* m_registry;
    RendererSystem m_renderer_system;
};

#endif