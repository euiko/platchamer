#ifndef GAME_HPP
#define GAME_HPP

#define MaxPolyVertexCount 64

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include "level_manager.hpp"
#include "../graphics/window.hpp"
#include "../libs/entcosy/src/entcosy/registry.hpp"
#include "../systems/renderer_system.hpp"

class Game
{
public:
    static LevelManager level_manager;
    Game(const std::string& title, int w, int h, Uint32 flags);
    ~Game() = default;
    int run();

private:
    void event();
    void update(double time);
    void render();

private:
    std::shared_ptr<entcosy::Registry> m_registry;
    platchamer::graphics::Window m_window;
    RendererSystem m_renderer_system;
};

#endif
