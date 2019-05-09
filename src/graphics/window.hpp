#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>

namespace platchamer
{
    namespace graphics
    {
        class Window
        {
        public:
            Window(const std::string& title, int w, int h, Uint32 flags);
            ~Window();
            SDL_Renderer* getRenderer() const noexcept;
            SDL_Window* getWindow();

        private:
            void* sdlNativeWindowHandle();
            bool sdlSetWindow();
            void configureSdl();
            void configureImgUi(const char* glsl_version);

        public:
            bool m_isOpen;
            SDL_Event m_event;
            SDL_GLContext gl_context;

        private:
            SDL_Window* m_window;
            SDL_Renderer* m_renderer;
            SDL_Texture* m_bgiTexture;
        };
    } // graphics
} // platchamer

#endif
