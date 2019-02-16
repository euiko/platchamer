#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>

class Window
{
public:
    ///
    /// Construct a window.
    ///
    /// \param title Title of the window.
    /// \param w Width of the window.
    /// \param h Height of the window.
    /// \param flags SDL2 Window flags.
    ///
    Window(const std::string& title, int w, int h, Uint32 flags);

    ///
    /// Clean up class data.
    ///
    ~Window();

    ///
    /// Retrieve our renderer.
    ///
    /// \return CONST pointer to SDL_Renderer object. We want it const because we don't want the pointer to change.
    ///
    SDL_Renderer* getRenderer() const noexcept;

public:
    ///
    /// Keep track of window state.
    ///
    bool m_isOpen;

    ///
    /// Union to hold event data.
    ///
    SDL_Event m_event;

private:
    ///
    /// Pointer to window data.
    ///
    SDL_Window* m_window;

    ///
    /// Pointer to renderer data.
    ///
    SDL_Renderer* m_renderer;
};

#endif