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
        ImGui::Begin("My First Tool", &ui_state->is_tool_active, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
                if (ImGui::MenuItem("Close", "Ctrl+W"))  { ui_state->is_tool_active = false; }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        // Edit a color (stored as ~4 floats)
        ImGui::ColorEdit4("Color", &ui_state->color);

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
    }
};

#endif
