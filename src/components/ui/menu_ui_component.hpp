#ifndef PLATCHAMER_COMPONENTS_UI_MENUUICOMPONENT_HPP
#define PLATCHAMER_COMPONENTS_UI_MENUUICOMPONENT_HPP

#include <entcosy/registry.hpp>

struct MenuUiComponent
{
    ENTCOSY_DECLARE_TYPE;

    int health;
    float color;
    bool is_tool_active;

    template<class Archive>
    void serialize(Archive &ar)
    {

    }
};


#endif
