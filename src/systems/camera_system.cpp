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

void CameraSystem::configure(std::shared_ptr<entcosy::Registry> registry)
{

}

void CameraSystem::unconfigure(std::shared_ptr<entcosy::Registry> registry)
{

}

void CameraSystem::update(std::shared_ptr<entcosy::Registry> registry, float deltaTime)
{
    registry->each<CameraTag, PositionComponent>([&](std::shared_ptr<entcosy::Entity> entity, CameraTag* camera_tag,
        PositionComponent* position_component)
    {
        CameraComponent* camera_component = entity->get<CameraComponent>();
        if(camera_component == nullptr)
            return;

        PositionComponent* object_position = camera_component->looked_object->get<PositionComponent>();

        position_component->pos.x = - (object_position->pos.x - (getmaxx()/2));
        // position_component->pos.y = - (object_position->pos.y - (getmaxy()/2));

    });
}
