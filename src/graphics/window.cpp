#include <cassert>
#include <bgfx/platform.h>
#include <imgui/imgui.h>
#include <imgui-sdl/imgui_sdl.h>
#include "../utils/imgui_impl_sdl.h"
#include "../utils/imgui_impl_opengl3.h"
#include <imgui-sdl/imgui_sdl.h>
#include <SDL2/SDL_syswm.h>
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif
extern "C" {
    #include <SDL2/SDL_bgi.h>
}
#include "window.hpp"

namespace platchamer
{
    namespace graphics
    {
        Window::Window(const std::string& title, int w, int h, Uint32 flags)
            :m_isOpen(true), m_window(nullptr), m_renderer(nullptr)
        {
            char* cTitle = new char[title.length()];
            cTitle = const_cast<char*>(title.c_str());
            setwinoptions(cTitle, -1, -1, flags);

            initwindow(w, h);

            m_window = bgi_window;

            if(!m_window) {
                std::string message = "Window failed to be created! SDL: ";
                message += SDL_GetError();
            }

            m_renderer = bgi_renderer;
            m_bgiTexture = bgi_texture;

            configureSdl();
            sdlSetWindow();

            bgfx::init();
            bgfx::reset(w, h, BGFX_RESET_NONE);
            bgfx::setViewRect(0, 0, 0, uint16_t(w), uint16_t(h));
            bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);

            if(!m_renderer) {
                std::string message = "Renderer failed to be created! SDL: ";
                message += SDL_GetError();
            }
        }

        Window::~Window()
        {
            ImGuiSDL::Deinitialize();
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
            SDL_GL_DeleteContext(gl_context);
            bgfx::shutdown();
            closegraph();
        }

        SDL_Renderer* Window::getRenderer() const noexcept
        {
            return m_renderer;
        }

        SDL_Window* Window::getWindow()
        {
            return m_window;
        }

        void* Window::sdlNativeWindowHandle()
        {
            SDL_SysWMinfo wmi;
            SDL_VERSION(&wmi.version);
            if (!SDL_GetWindowWMInfo(m_window, &wmi) )
            {
                return NULL;
            }

#	        if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		    if ENTRY_CONFIG_USE_WAYLAND
            wl_egl_window *win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
            if(!win_impl)
            {
                int width, height;
                SDL_GetWindowSize(_window, &width, &height);
                struct wl_surface* surface = wmi.info.wl.surface;
                if(!surface)
                    return nullptr;
                win_impl = wl_egl_window_create(surface, width, height);
                SDL_SetWindowData(_window, "wl_egl_window", win_impl);
            }
            return (void*)(uintptr_t)win_impl;
#   		else
            return (void*)wmi.info.x11.window;
#   		endif
#   	elif BX_PLATFORM_OSX
            return wmi.info.cocoa.window;
#   	elif BX_PLATFORM_WINDOWS
            return wmi.info.win.window;
#   	elif BX_PLATFORM_STEAMLINK
            return wmi.info.vivante.window;
#   	endif // BX_PLATFORM_
        }

        bool Window::sdlSetWindow()
        {
            SDL_SysWMinfo wmi;
            SDL_VERSION(&wmi.version);
            if (!SDL_GetWindowWMInfo(m_window, &wmi) )
            {
                return false;
            }

            bgfx::PlatformData pd;
#	        if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		        if ENTRY_CONFIG_USE_WAYLAND
            pd.ndt          = wmi.info.wl.display;
#		        else
            pd.ndt          = wmi.info.x11.display;
#		        endif
#	        elif BX_PLATFORM_OSX
            pd.ndt          = NULL;
#	        elif BX_PLATFORM_WINDOWS
            pd.ndt          = NULL;
#	        elif BX_PLATFORM_STEAMLINK
            pd.ndt          = wmi.info.vivante.display;
#	        endif // BX_PLATFORM_
            pd.nwh          = sdlNativeWindowHandle();

            pd.context      = NULL;
            pd.backBuffer   = NULL;
            pd.backBufferDS = NULL;
            bgfx::setPlatformData(pd);

            return true;
        }

        void Window::configureSdl ()
        {
        #if __APPLE__
            // GL 3.2 Core + GLSL 150
            const char glslVersion[] = "#version 150";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        #else
            // GL 3.0 + GLSL 130
            const char glslVersion[] = "#version 130";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        #endif

            // Create window with graphics context
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
            SDL_DisplayMode current;
            SDL_GetCurrentDisplayMode(0, &current);
            gl_context = SDL_GL_CreateContext(m_window);
            SDL_GL_SetSwapInterval(1); // Enable vsync

        #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
            bool err = gl3wInit() != 0;
        #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
            bool err = glewInit() != GLEW_OK;
        #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
            bool err = gladLoadGL() == 0;
        #else
            bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
        #endif
            if (err)
            {
                assert("Failed to initialize OpenGL loader!\n");
            }

            configureImgUi(glslVersion);
        }


        void Window::configureImgUi(const char* glsl_version)
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            int w, h;
            SDL_GetWindowSize(m_window, &w, &h);

            ImGui::CreateContext();
            ImGuiSDL::Initialize(m_renderer, w, h);

            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

            ImGui::StyleColorsDark();

            // Setup Platform/Renderer bindings
            ImGui_ImplSDL2_InitForOpenGL(m_window, gl_context);
            ImGui_ImplOpenGL3_Init(glsl_version);

            // Load Fonts
            // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
            // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
            // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
            // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
            // - Read 'misc/fonts/README.txt' for more instructions and details.
            // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
            //io.Fonts->AddFontDefault();
            //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
            //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
            //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
            //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
            //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
            //IM_ASSERT(font != NULL);
        }

    } // graphics
} // platchamer
