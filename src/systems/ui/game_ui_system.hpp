#ifndef PLATCHAMER_SYSTEMS_UI_GAMEUISYSTEMS_HPP
#define PLATCHAMER_SYSTEMS_UI_GAMEUISYSTEMS_HPP

#include <entcosy/registry.hpp>
#include <imgui/imgui.h>
#include <imgui-sdl/imgui_sdl.h>
#include "../../utils/imgui_impl_sdl.h"
#include "../../components/ui/game_ui_component.hpp"

class GameUiSystem : public entcosy::UiSystem<GameUiComponent>
{
    std::string getUiName() const
    {
        return "game-ui";
    }

    void updateUi(std::shared_ptr<entcosy::Registry> registry, GameUiComponent* ui_state, float delta_time)
    {

    }

    void renderUi(std::shared_ptr<entcosy::Registry> registry)
    {
        GameUiComponent* ui_state = getUiState(registry);

        ImGui::Begin("Game Over Menu", &ui_state->is_tool_active, ImGuiWindowFlags_MenuBar);

        // Display contents in a scrolling region
        ImGui::TextColored(ImVec4(1,1,0,1), "GAME OVER");

        ImGui::End();
    }
};

#endif
