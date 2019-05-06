#ifndef ENEMY_TAG_HPP
#define ENEMY_TAG_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

struct EnemyTag
{
    ENTCOSY_DECLARE_TYPE;

    template<class Archive>
    void serialize(Archive &ar)
    {

    }
};

#endif
