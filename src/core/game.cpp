
#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include <fstream>
#include <bgfx/bgfx.h>
extern "C" {
    #include <sdl_bgi/graphics.h>
}
#include "game.hpp"
#include "../libs/stb_image.h"
#include "factories.hpp"
#include "../systems/camera_system.hpp"
#include "../systems/bullet_system.hpp"
#include "../systems/polygon_system.hpp"
#include "../systems/physics_system.hpp"
#include "../systems/player_control_system.hpp"
#include "../events/reset_player_state_event.hpp"
#include "../events/collide_event.hpp"
#include "../events/keyboard_event.hpp"
#include "../components/position_component.hpp"
#include "../components/camera_component.hpp"
#include "../components/polygon_component.hpp"
#include "../components/circle_component.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../components/circle_collider_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/camera_tag.hpp"
#include "../tags/ground_tag.hpp"
#include "../tags/player_tag.hpp"
#include "../tags/enemy_tag.hpp"
#include "../tags/bullet_tag.hpp"

ENTCOSY_INITIALIZATION;
ENTCOSY_DEFINE_TYPE(CameraComponent);
ENTCOSY_DEFINE_TYPE(PolygonComponent);
ENTCOSY_DEFINE_TYPE(CircleComponent);
ENTCOSY_DEFINE_TYPE(CircleColliderComponent);
ENTCOSY_DEFINE_TYPE(PositionComponent);
ENTCOSY_DEFINE_TYPE(PolygonColliderComponent);
ENTCOSY_DEFINE_TYPE(RigidBodyComponent);

ENTCOSY_DEFINE_TYPE(CameraTag);
ENTCOSY_DEFINE_TYPE(PlayerTag);
ENTCOSY_DEFINE_TYPE(EnemyTag);
ENTCOSY_DEFINE_TYPE(GroundTag);
ENTCOSY_DEFINE_TYPE(BulletTag);

ENTCOSY_REGISTER_TYPE(KeyboardEvent);
ENTCOSY_REGISTER_TYPE(CollideEvent);
ENTCOSY_REGISTER_TYPE(ResetPlayerStateEvent);

// CEREAL_REGISTER_TYPE(CircleColliderComponent);
// CEREAL_REGISTER_TYPE(PolygonColliderComponent);
// CEREAL_REGISTER_POLYMORPHIC_RELATION(Collider, CircleColliderComponent);
// CEREAL_REGISTER_POLYMORPHIC_RELATION(Collider, PolygonColliderComponent);

Game::Game(const std::string& title, int w, int h, Uint32 flags)
    :m_window(title, w, h, flags)
{
    // m_registry = std::make_shared<entcosy::Registry>();

    {
        std::cout << "Loading... \n";
        std::ifstream is("level.bin", std::ios::binary);
        cereal::BinaryInputArchive archive(is);
        archive(m_registry);
        is.close();
        std::cout << "Loaded \n";
    }

    m_registry->registerSystem(std::make_shared<CameraSystem>());
    m_registry->registerSystem(std::make_shared<PolygonSystem>());
    m_registry->registerSystem(std::make_shared<PhysicsSystem>(50.0f));
    m_registry->registerSystem(std::make_shared<PlayerControlSystem>());
    m_registry->registerSystem(std::make_shared<BulletSystem>());

    // std::shared_ptr<entcosy::Entity> player = makePlayer(m_registry, getmaxx() / 2-100, getmaxy() / 2);
    // makeCamera(m_registry, player);
    // makeEnemy(m_registry, getmaxx() / 2 + 100, getmaxy() / 2 - 100);
    // makeBlock(m_registry, getmaxx() / 2, getmaxy() - 100);
    // makeBlock(m_registry, getmaxx() / 2 + 775, getmaxy() - 100);
    // makeBlock(m_registry, getmaxx() / 2 + 250, getmaxy() - 300);
    // makeBlock(m_registry, getmaxx() / 2 - 400, getmaxy() - 100, 1.00f);
    // makeBlock(m_registry, getmaxx() / 2 + 1175, getmaxy()+100, M_PI/2 );
    // makeBlock(m_registry, getmaxx() / 2 + 1575, getmaxy() - 290);

    // {
    //     std::ofstream os("level.bin", std::ios::binary);
    //     cereal::BinaryOutputArchive archive(os);
    //     archive(m_registry);
    //     os.close();
    // }
}

int Game::run()
{
    double time = 0;
    double accumulator = 0.0;

    const double deltaTime = 1000.0 / 60.0;

    double currentTime = SDL_GetTicks();
    SDL_SetRenderDrawColor(m_window.getRenderer(), 0, 0, 0, 0);

    // char fps[3];
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
        // sprintf(fps, "%d", (int)(1000/frameTime));
        // outtextxy(40, 40, fps);
        // std::cout << "FPS: " << fps << "\n";
        // std::cout << "ACCM: " << accumulator << "\n";
    }


    bgfx::shutdown();
    // m_registry->cleanup();
    // m_registry->destroyRegistry();

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
    m_registry->emit<ResetPlayerStateEvent>({});
    m_registry->update(time);
}

void Game::render()
{
    cleardevice();
    SDL_RenderClear(m_window.getRenderer());

    m_renderer_system.render(&m_window, m_registry);

    refresh();
    SDL_RenderPresent(m_window.getRenderer());
}
