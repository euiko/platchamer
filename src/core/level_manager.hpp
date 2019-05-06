#ifndef PLATCHAMER_CORE_LEVELMANAGER_HPP
#define PLATCHAMER_CORE_LEVELMANAGER_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

class LevelManager
{
public:
    std::shared_ptr<entcosy::Registry> getRegistry()
    {
        return m_registry;
    }


private:
    std::shared_ptr<entcosy::Registry> m_registry;
};

#endif
