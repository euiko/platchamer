#ifndef THORN_TAG_HPP
#define THORN_TAG_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

struct ThornTag
{
    ENTCOSY_DECLARE_TYPE;

    template<class Archive>
    void serialize(Archive &ar)
    {

    }
};

#endif
