#ifndef PLAYER_TAG_HPP
#define PLAYER_TAG_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

struct PlayerTag
{
    ENTCOSY_DECLARE_TYPE;
    bool is_ground = true;

    template<class Archive>
    void serialize(Archive &ar)
    {
        ar(is_ground);
    }
};

#endif
