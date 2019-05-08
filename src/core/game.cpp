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
    level_manager.load("level.bin");

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
    // m_registry->registerSystem(std::make_shared<CameraSystem>());
    // m_registry->registerSystem(std::make_shared<PolygonSystem>());
    // m_registry->registerSystem(std::make_shared<PhysicsSystem>(50.0f));
    // m_registry->registerSystem(std::make_shared<PlayerControlSystem>());
    // m_registry->registerSystem(std::make_shared<BulletSystem>());

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
            update(accumulator);

            accumulator -= deltaTime;
            time += deltaTime;
        }

        render(io);
        // SDL_RenderPresent(m_window.getRenderer());
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
                default:
                    level_manager.getRegistry()->emit<KeyboardEvent>({m_window.m_event.key.keysym.sym});
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
    std::shared_ptr<entcosy::Registry> registry = level_manager.getRegistry();
    registry->emit<ResetPlayerStateEvent>({});
    registry->update(time);
}

void Game::render(ImGuiIO& io)
{
    cleardevice();
    SDL_RenderClear(m_window.getRenderer());

    bool my_tool_active;

    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    m_renderer_system.render(&m_window, level_manager.getRegistry());
    refresh();

    ImGui_ImplSDL2_NewFrame(m_window.getWindow());
    ImGui::NewFrame();
    ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    // Edit a color (stored as ~4 floats)
    ImGui::ColorEdit4("Color", &color);

    // Plot some values
    const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
    ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

    // Display contents in a scrolling region
    ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();
    ImGui::End();

    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());

    SDL_RenderPresent(m_window.getRenderer());
}
