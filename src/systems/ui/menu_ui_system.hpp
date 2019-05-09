#ifndef PLATCHAMER_SYSTEMS_UI_MENUUICOMPONENT_HPP
#define PLATCHAMER_SYSTEMS_UI_MENUUICOMPONENT_HPP

#include <array>
#include <entcosy/registry.hpp>
#include <imgui/imgui.h>
#include <imgui-sdl/imgui_sdl.h>
#include "../../utils/imgui_impl_sdl.h"
#include "../../components/ui/menu_ui_component.hpp"

// MenuUiComponent::__ENTCOSY_type_reg.getIndex();

// template<> const char * entcosy::getTypeName<id>() {
//     std::cout << "Halo";
//     return "halo";
// }

class MenuUiSystem : public entcosy::UiSystem<MenuUiComponent>
{
    std::string getUiName() const
    {
        return "menu-ui";
    }

    void updateUi(std::shared_ptr<entcosy::Registry> registry, MenuUiComponent* ui_state, float delta_time)
    {

    }

    void renderUi(std::shared_ptr<entcosy::Registry> registry)
    {
        MenuUiComponent* ui_state = getUiState(registry);

        mainMenuBar();

        ImGui::Begin("Scene"); // begin first window
        registry->all([&](std::shared_ptr<entcosy::Entity> entity)
        {
            if (ImGui::TreeNode(entity->getEntityName()))
            {
                ImGui::TreePop();
            }
        });
        ImGui::End();
    }

    void mainMenuBar()
    {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("Main"))
        {
            ImGui::MenuItem("New Scene");
            ImGui::MenuItem("Load Scene");
            ImGui::MenuItem("Save Scene");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::MenuItem("Undo");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Entity"))
        {
            ImGui::MenuItem("Add Entity");
            ImGui::MenuItem("Clone Entity");
            ImGui::MenuItem("Save Entity");
            ImGui::MenuItem("Delete Entity");
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
};

#endif
