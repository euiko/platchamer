#ifndef PLATCHAMER_COMPONENTS_CAMERA_HPP
#define PLATCHAMER_COMPONENTS_CAMERA_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

struct CameraComponent {
    ENTCOSY_DECLARE_TYPE;

    std::shared_ptr<entcosy::Entity> looked_object;

    CameraComponent(std::shared_ptr<entcosy::Entity> looked_object) : looked_object(looked_object) 
    {}
};


#endif