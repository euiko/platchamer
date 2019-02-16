#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>

class Game
{
public:
    Game(const std::string& title, int w, int h, Uint32 flags);
    ~Game() = default;
    int run();

private:
    void event();
    void update(double time);
    void render();

private:
    Window m_window;
    entt::DefaultRegistry m_registry;
}

#endif