#ifndef PLATCHAMER_SYSTEMS_UI_MENUUICOMPONENT_HPP
#define PLATCHAMER_SYSTEMS_UI_MENUUICOMPONENT_HPP

#include <array>
#include <array>
#include <entcosy/registry.hpp>
#include <imgui/imgui.h>
#include <imgui-sdl/imgui_sdl.h>
#include "../../utils/imgui_impl_sdl.h"
#include "../../types/vect2.hpp"
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

        if(ui_state != nullptr)
        {
            mainMenuBar();
            sceneWindow(registry, ui_state);
            componentEditor(registry, ui_state);
        }

    }

    void componentEditor(std::shared_ptr<entcosy::Registry> registry, MenuUiComponent* ui_state)
    {
        if(ui_state->is_tool_active)
        {
            rttr::type componentType = rttr::type::get(ui_state->current_variant);
            std::string title("Edit ");
            title += componentType.get_name().data();
            ImGui::Begin(title.data());
            for(auto &property : componentType.get_properties())
            {
                if(!property.is_valid())
                    continue;

                std::string subTitle(property.get_type().get_name().data());
                subTitle += std::string(": ") + std::string(property.get_name().data());

                ImGui::Text(subTitle.data());
                // ImGui::SameLine();
                rttr::variant valueVariant = property.get_value(ui_state->current_variant);
                if(!valueVariant.is_valid())
                    continue;
                if(valueVariant.is_type<Vect2>())
                {
                    Vect2 inVect2;
                    rttr::type vect2Type = rttr::type::get(valueVariant);
                    rttr::property xProperty = vect2Type.get_property("x");
                    rttr::property yProperty = vect2Type.get_property("y");
                    inVect2.x = xProperty.get_value(valueVariant).to_float();
                    inVect2.y = yProperty.get_value(valueVariant).to_float();

                    if(ImGui::InputFloat("x", &inVect2.x, 1.0f))
                    {
                        // std::cout << x << "\n";
                        property.set_value(ui_state->current_variant, inVect2);
                    }
                    if(ImGui::InputFloat("y", &inVect2.y, 1.0f))
                    {
                        property.set_value(ui_state->current_variant, inVect2);
                    }
                }else if(valueVariant.is_type<float>())
                {
                    float val = valueVariant.to_float();
                    rttr::string_view inputTitle = property.get_name();
                    std::cout << inputTitle << "\n";
                    if(ImGui::InputFloat(inputTitle.data() , &val, 1.0f))
                    {
                        property.set_value(ui_state->current_variant, val);
                    }
                }else if(valueVariant.is_type<int>())
                {
                    int val = valueVariant.to_int();
                    // std::cout << val << "\n";
                    if(ImGui::InputInt(property.get_name().data(), &val, 1.0f))
                    {
                        property.set_value(ui_state->current_variant, val);
                    }
                } else if(valueVariant.is_type<bool>())
                {
                    bool val = (bool)valueVariant.to_int();
                    // std::cout << val << "\n";
                    if(ImGui::InputInt(property.get_name().data(), &val, 1.0f))
                    {
                        property.set_value(ui_state->current_variant, val);
                    }
                }
            }
            ImGui::End();
        }
    }

    void sceneWindow(std::shared_ptr<entcosy::Registry> registry, MenuUiComponent* ui_state)
    {
        ImGui::Begin("Scene"); // begin first window
        registry->all([&](std::shared_ptr<entcosy::Entity> entity)
        {
            if (ImGui::TreeNode(entity->getEntityName()))
            {
                entity->all([&](rttr::type& componentType, rttr::variant& value)
                {
                    if(ImGui::TreeNodeEx(componentType.get_name().data(), ImGuiTreeNodeFlags_Leaf))
                    {
                        if (ImGui::IsItemClicked())
                        {
                            ui_state->is_tool_active = true;
                            ui_state->active_component_name = componentType.get_name();
                            ui_state->current_variant = value;
                        }
                        ImGui::TreePop();
                    }
                });
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
