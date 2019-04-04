extern "C" {
    #include <sdl_bgi/graphics.h>
}

#include "camera_system.hpp"
#include "../components/position_component.hpp"
#include "../components/camera_component.hpp"
#include "../tags/camera_tag.hpp"

CameraSystem::CameraSystem() 
{

}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::configure(Registry* registry) 
{
      
}

void CameraSystem::unconfigure(Registry* registry)
{
    
}

void CameraSystem::tick(Registry* registry, float deltaTime)
{
    registry->each<CameraTag, PositionComponent>([&](Entity* entity, ComponentHandle<CameraTag> camera_tag, 
        ComponentHandle<PositionComponent> position_component)
    {
        ComponentHandle<CameraComponent> camera_component = entity->get<CameraComponent>();
        if(!camera_component.isValid())
            return;
        
        ComponentHandle<PositionComponent> object_position = camera_component->looked_object->get<PositionComponent>();

        position_component->pos.x = - (object_position->pos.x - (getmaxx()/2));
        // position_component->pos.y = - (object_position->pos.y - (getmaxy()/2));

    });
}