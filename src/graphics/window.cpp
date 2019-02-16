#include "window.hpp"
extern "C" {
    #include <SDL2/SDL_bgi.h>
}

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