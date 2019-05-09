#ifndef PLATCHAMER_COMPONENTS_UI_GAMEUICOMPONENT_HPP
#define PLATCHAMER_COMPONENTS_UI_GAMEUICOMPONENT_HPP

#include <entcosy/registry.hpp>

struct GameUiComponent
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
