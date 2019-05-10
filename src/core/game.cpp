#include <vector>
#include <fstream>
#include <imgui/imgui.h>
#include <imgui-sdl/imgui_sdl.h>
#include "../utils/imgui_impl_sdl.h"
#include "../utils/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <bgfx/bgfx.h>
#include <SDL2/SDL_mouse.h>
extern "C" {
    #include <sdl_bgi/graphics.h>
}
#include "game.hpp"
#include "../libs/stb_image.h"
#include "factories.hpp"
#include "../systems/ui/game_ui_system.hpp"
#include "../systems/ui/menu_ui_system.hpp"

// CEREAL_REGISTER_TYPE(CircleColliderComponent);
// CEREAL_REGISTER_TYPE(PolygonColliderComponent);
// CEREAL_REGISTER_POLYMORPHIC_RELATION(Collider, CircleColliderComponent);
// CEREAL_REGISTER_POLYMORPHIC_RELATION(Collider, PolygonColliderComponent);

Game::Game(const std::string& title, int w, int h, Uint32 flags)
    :m_window(title, w, h, flags)
{
    m_registry = std::make_shared<entcosy::Registry>();
    // level_manager.load("level.bin");

    // std::cout << " Use count: " << level_manager.getRegistry().use_count() << "\n";
    // level_manager.getRegistry()->clear();

    // {
    //     std::ifstream is("level.bin", std::ios::binary);
    //     cereal::BinaryInputArchive archive(is);
    //     archive(m_registry);
    //     // m_registry->clear();
    //     is.close();
    // }
    // std::cout << " Use count: " << m_registry.use_count() << "\n";
    m_registry->registerSystem(std::make_shared<CameraSystem>());
    m_registry->registerSystem(std::make_shared<PolygonSystem>());
    m_registry->registerSystem(std::make_shared<PhysicsSystem>(50.0f));
    m_registry->registerSystem(std::make_shared<PlayerControlSystem>());
    m_registry->registerSystem(std::make_shared<BulletSystem>());

    m_registry->registerUi(std::make_shared<MenuUiSystem>());
    m_registry->registerUi(std::make_shared<GameUiSystem>());

    std::shared_ptr<entcosy::Entity> player = makePlayer(m_registry, getmaxx() / 2-100, getmaxy() / 2);
    makeCamera(m_registry, player);
    makeEnemy(m_registry, getmaxx() / 2 + 100, getmaxy() / 2 - 100);
    makeBlock(m_registry, getmaxx() / 2, getmaxy() - 100);
    makeBlock(m_registry, getmaxx() / 2 + 775, getmaxy() - 100);
    makeBlock(m_registry, getmaxx() / 2 + 250, getmaxy() - 300);
    makeBlock(m_registry, getmaxx() / 2 - 400, getmaxy() - 100, 1.00f);
    makeBlock(m_registry, getmaxx() / 2 + 1175, getmaxy()+100, M_PI/2 );
    makeBlock(m_registry, getmaxx() / 2 + 1575, getmaxy() - 290);
    makeThorn(m_registry, getmaxx() / 2 + 1575, getmaxy() - 350);

    {
        std::ofstream os("level.bin", std::ios::binary);
        cereal::BinaryOutputArchive archive(os);
        archive(m_registry);
        os.close();
    }
}

int Game::run()
{
    double time = 0;
    double accumulator = 0.0;

    const double deltaTime = 1000.0 / 60.0;

    double currentTime = SDL_GetTicks();
    SDL_SetRenderDrawColor(m_window.getRenderer(), 0, 0, 0, 0);

    ImGuiIO& io = ImGui::GetIO();
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

            if(m_registry->isUiActive<MenuUiComponent>())
            {
                update(accumulator);
            }

            accumulator -= deltaTime;
            time += deltaTime;
        }

        render(io);
        // SDL_RenderPresent(m_window.getRenderer());
        // sprintf(fps, "%d", (int)(1000/frameTime));
        // outtextxy(40, 40, fps);
        // std::cout << "FPS: " << fps << "\n";
        // std::cout << "ACCM: " << accumulator << "\n";
    };

    // m_registry->cleanup();
    // m_registry->destroyRegistry();

    return EXIT_SUCCESS;
}

void Game::event()
{
    level_manager.swap();
    while (SDL_PollEvent(&m_window.m_event) != 0)
    {

        ImGui_ImplSDL2_ProcessEvent(&m_window.m_event);
        switch (m_window.m_event.type)
        {
            case SDL_QUIT: {
                m_window.m_isOpen = false;
                break;
            }
            case SDL_MOUSEWHEEL: {
                if (m_window.m_event.wheel.y > 0) {
                    m_mouseWheel = 1;
                }
                if (m_window.m_event.wheel.y < 0) {
                    m_mouseWheel = -1;
                }
                break;
            }
            case SDL_KEYDOWN: {
                switch (m_window.m_event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    m_window.m_isOpen = false;
                    break;
                case SDLK_r:
                    level_manager.load("level.bin");
                    break;
                case SDLK_c:
                    m_registry->changeUi<MenuUiComponent>();
                    break;
                case SDLK_v:
                    m_registry->changeUi<GameUiComponent>();
                    break;
                default:
                    m_registry->emit<KeyboardEvent>({m_window.m_event.key.keysym.sym});
                    break;
                }
                break;
            }
        }

    }
}

void Game::update(double time)
{
    // std::cout << "Use count: " << level_manager.getRegistry().use_count() << "\n";
    std::shared_ptr<entcosy::Registry> registry = m_registry;
    registry->emit<ResetPlayerStateEvent>({});
    registry->update(time);
}

void Game::render(ImGuiIO& io)
{
    cleardevice();
    SDL_RenderClear(m_window.getRenderer());


    m_renderer_system.render(&m_window, m_registry);
    refresh();

    ImGui_ImplSDL2_NewFrame(m_window.getWindow());
    ImGui::NewFrame();
    m_registry->renderUi();
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());

    SDL_RenderPresent(m_window.getRenderer());
}
