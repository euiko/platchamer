#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include "../core/ecs/registry.hpp"
#include "../graphics/window.hpp"

class RendererSystem {
    public:
        RendererSystem() = default;
        ~RendererSystem() = default;

        void render(Window* window, ecs::Registry* registry);
        
};

#endif