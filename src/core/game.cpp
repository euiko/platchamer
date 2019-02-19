
#define STB_IMAGE_IMPLEMENTATION

#include <vector>
extern "C" {
    #include <sdl_bgi/graphics.h>
}
#include "game.hpp"
#include "../libs/stb_image.h"
#include "../systems/polygon_system.hpp"
#include "../components/position_component.hpp"
#include "../components/polygon_component.hpp"

ECS_TYPE_IMPLEMENTATION;
ECS_DEFINE_TYPE(PolygonComponent);
ECS_DEFINE_TYPE(PositionComponent);

Game::Game(const std::string& title, int w, int h, Uint32 flags)
    :m_window(title, w, h, flags)
{
    m_registry = ecs::Registry::createRegistry();
    m_registry->registerSystem(new PolygonSystem());
    ecs::Entity* player = m_registry->create();
    player->assign<PositionComponent>(getmaxx() / 2, getmaxy() / 2, 45.0f);
    std::vector<Vect2> shape = {
        {0, 0},
        {50, 0},
        {50, 50},
        {0, 50},
    };
    
    player->assign<PolygonComponent>(shape);

}

int Game::run() {

    double time = 0;
    double accumulator = 0.0;

    const double deltaTime = 1000.0 / 60.0;

    double currentTime = SDL_GetTicks();
    SDL_SetRenderDrawColor(m_window.getRenderer(), 0, 0, 0, 0);
    // std::unique_ptr<std::thread> renderThread;
    while (m_window.m_isOpen)
    {
        const double newTime = SDL_GetTicks();
        const double frameTime = newTime - currentTime;
        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= deltaTime)
        {
            event();
            update(accumulator);

            accumulator -= deltaTime;
            time += deltaTime;
        }

        render();

        std::cout << "TIME: " << time << "\n";
        std::cout << "ACCM: " << accumulator << "\n";
    }
    m_registry->cleanup();
    m_registry->destroyRegistry();

    return EXIT_SUCCESS;
}

void Game::event()
{
    while (SDL_PollEvent(&m_window.m_event) != 0)
    {
        switch (m_window.m_event.type)
        {
        case SDL_QUIT:
            m_window.m_isOpen = false;
            break;

        case SDL_KEYDOWN:
            switch (m_window.m_event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                m_window.m_isOpen = false;
                break;
            }
            break;
        }

    }
}

void Game::update(double time)
{
    m_registry->tick(time);   
}

void Game::render()
{
    cleardevice();
    SDL_RenderClear(m_window.getRenderer());

    m_renderer_system.render(&m_window, m_registry);

    refresh();
    SDL_RenderPresent(m_window.getRenderer());
}