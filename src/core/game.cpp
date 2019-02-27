
#define STB_IMAGE_IMPLEMENTATION

#include <vector>
extern "C" {
    #include <sdl_bgi/graphics.h>
}
#include "game.hpp"
#include "../libs/stb_image.h"
#include "../core/physics/shapes/polygon_collider.hpp"
#include "../systems/polygon_system.hpp"
#include "../systems/physics_system.hpp"
#include "../systems/player_control_system.hpp"
#include "../events/keyboard_event.hpp"
#include "../components/position_component.hpp"
#include "../components/physics_component.hpp"
#include "../components/polygon_component.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/player_tag.hpp"

ECS_TYPE_IMPLEMENTATION;
ECS_DEFINE_TYPE(PolygonComponent);
ECS_DEFINE_TYPE(PositionComponent);
ECS_DEFINE_TYPE(PhysicsComponent);
ECS_DEFINE_TYPE(PolygonColliderComponent);
ECS_DEFINE_TYPE(RigidBodyComponent);
ECS_DEFINE_TYPE(PlayerTag);
ECS_DEFINE_TYPE(KeyboardEvent);

Game::Game(const std::string& title, int w, int h, Uint32 flags)
    :m_window(title, w, h, flags)
{
    m_registry = ecs::Registry::createRegistry();
    m_registry->registerSystem(new PolygonSystem());
    m_registry->registerSystem(new PlayerControlSystem());
    // m_registry->registerSystem(new PhysicsSystem());
    ecs::Entity* player = m_registry->create();
    player->assign<PositionComponent>(0, 0, 0.0f);
    //Kotak biasa
    std::vector<Vect2> shape = {
        {109.58, 54.65},
        {93.19, 49.34},
        {73.09, 47.51},
        {60.30, 43.86},
        {56.65, 43.86},
        {39.91, 23.76},
        {43.85, 23.76},
        {46.42, 23.50},
        {47.51, 22.84},
        {46.42, 22.18},
        {43.85, 21.93},
        {38.37, 21.93},
        {29.24, 21.93},
        {25.58, 21.93},
        {25.58, 23.75},
        {29.24, 23.75},
        {29.24, 47.51},
        {20.10, 47.51},
        {9.14, 34.72},
        {3.65, 34.72},
        {1.83, 36.55},
        {1.83, 47.51},
        {3.65, 47.51},
        {3.65, 49.34},
        {10.96, 49.34},
        {10.96, 49.79},
        {0.00, 51.16},
        {0.00, 58.47},
        {10.96, 59.84},
        {10.96, 60.30},
        {3.65, 60.30},
        {3.65, 62.13},
        {1.83, 62.13},
        {1.83, 73.09},
        {3.65, 74.92},
        {9.14, 74.92},
        {20.10, 62.13},
        {29.24, 62.13},
        {29.24, 85.88},
        {25.58, 85.88},
        {25.58, 87.71},
        {29.24, 87.71},
        {38.37, 87.71},
        {43.85, 87.71},
        {46.42, 87.45},
        {47.51, 86.79},
        {46.42, 86.14},
        {43.85, 85.88},
        {39.91, 85.88},
        {56.65, 65.78},
        {60.30, 65.78},
        {73.09, 62.13},
        {93.19, 60.30},
        {109.64, 54.82},
        {109.58, 54.65},
    };
    player->assign<PolygonComponent>(shape, BLUE, 1.0f);
    player->assign<PlayerTag>();
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
            default:
                m_registry->emit<KeyboardEvent>({m_window.m_event.key.keysym.sym});
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