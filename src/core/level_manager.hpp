#ifndef PLATCHAMER_CORE_LEVELMANAGER_HPP
#define PLATCHAMER_CORE_LEVELMANAGER_HPP

#include <fstream>
#include "../libs/entcosy/src/entcosy/registry.hpp"
#include "../systems/camera_system.hpp"
#include "../systems/bullet_system.hpp"
#include "../systems/polygon_system.hpp"
#include "../systems/physics_system.hpp"
#include "../systems/player_control_system.hpp"

class LevelManager
{
public:

    LevelManager();

    std::shared_ptr<entcosy::Registry> getRegistry();

    void load(const char* file);

    void save(const char* file);

    bool swap();

private:
    std::vector<std::shared_ptr<entcosy::Registry>> m_registries;
    bool m_defferedLoad = false;
};

#endif
