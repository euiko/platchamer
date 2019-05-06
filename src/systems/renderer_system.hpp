#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"
#include "../graphics/window.hpp"

class RendererSystem {
    public:
        RendererSystem() = default;
        ~RendererSystem() = default;

        void render(platchamer::graphics::Window* window, std::shared_ptr<entcosy::Registry> registry);

};

#endif
