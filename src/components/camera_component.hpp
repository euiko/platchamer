#ifndef PLATCHAMER_COMPONENTS_CAMERA_HPP
#define PLATCHAMER_COMPONENTS_CAMERA_HPP

#include "../core/ecs/registry.hpp"

struct CameraComponent {
    ECS_DECLARE_TYPE;

    ecs::Entity* looked_object;

    CameraComponent(ecs::Entity* looked_object) : looked_object(looked_object) 
    {}
};


#endif