#ifndef PLATCHAMER_TAGS_CAMERA_HPP
#define PLATCHAMER_TAGS_CAMERA_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

struct CameraTag
{
    ENTCOSY_DECLARE_TYPE;

    template<class Archive>
    void serialize(Archive &ar)
    {

    }
};

#endif
