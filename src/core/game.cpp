
#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include <bgfx/bgfx.h>
extern "C" {
    #include <sdl_bgi/graphics.h>
}
#include "game.hpp"
#include "../libs/stb_image.h"
#include "factories.hpp"
#include "../systems/bullet_system.hpp"
#include "../systems/polygon_system.hpp"
#include "../systems/physics_system.hpp"
#include "../systems/player_control_system.hpp"
#include "../events/keyboard_event.hpp"
#include "../components/position_component.hpp"
#include "../components/polygon_component.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/player_tag.hpp"
#include "../tags/enemy_tag.hpp"
#include "../tags/bullet_tag.hpp"

ECS_TYPE_IMPLEMENTATION;
ECS_DEFINE_TYPE(PolygonComponent);
ECS_DEFINE_TYPE(PositionComponent);
ECS_DEFINE_TYPE(PolygonColliderComponent);
ECS_DEFINE_TYPE(RigidBodyComponent);

ECS_DEFINE_TYPE(PlayerTag);
ECS_DEFINE_TYPE(EnemyTag);
ECS_DEFINE_TYPE(BulletTag);

ECS_DEFINE_TYPE(KeyboardEvent);

Game::Game(const std::string& title, int w, int h, Uint32 flags)
    :m_window(title, w, h, flags)
{
    m_registry = ecs::Registry::createRegistry();
    m_registry->registerSystem(new PolygonSystem());
    m_registry->registerSystem(new PlayerControlSystem());
    m_registry->registerSystem(new BulletSystem());
    m_registry->registerSystem(new PhysicsSystem());
    makePlayer(m_registry, getmaxx() / 2-100, getmaxy() / 2);
    makeEnemy(m_registry, getmaxx() / 2 + 100, getmaxy() / 2 - 100);
    makeBlock(m_registry, getmaxx() / 2, getmaxy() - 100);
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

	
    bgfx::shutdown();
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