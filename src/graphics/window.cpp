#include <bgfx/platform.h>
#include <SDL2/SDL_syswm.h>
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
            
            {
                SDL_SysWMinfo wmInfo;
                SDL_VERSION(&wmInfo.version);
                SDL_GetWindowWMInfo(m_window, &wmInfo);

                auto native_window = wmInfo.info.x11.window;
                bgfx::PlatformData pd;
                // // pd.ndt = glfwGetX11Display();
                pd.nwh = (void*)native_window;
                pd.context = nullptr;
                pd.backBuffer = nullptr;
                pd.backBufferDS = nullptr;
                bgfx::setPlatformData(pd);
            }
            
            bgfx::init();

            bgfx::reset(w, h, BGFX_RESET_NONE);
            bgfx::setViewRect(0, 0, 0, uint16_t(w), uint16_t(h));
            bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);
            
            if(!m_window) {
                std::string message = "Window failed to be created! SDL: ";
                message += SDL_GetError();
            }

            m_renderer = bgi_renderer;
            if(!m_renderer) {
                std::string message = "Renderer failed to be created! SDL: ";
                message += SDL_GetError();
            }
        }

        Window::~Window()
        {
            closegraph();
        }

        SDL_Renderer* Window::getRenderer() const noexcept
        {
            return m_renderer;
        }
    } // graphics 
} // platchamer