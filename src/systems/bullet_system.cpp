extern "C" {
    #include <sdl_bgi/graphics.h>
}

#include "bullet_system.hpp"
#include "../tags/bullet_tag.hpp"
#include "../components/position_component.hpp"

BulletSystem::BulletSystem()
{

}

BulletSystem::~BulletSystem()
{

}

void BulletSystem::configure(std::shared_ptr<entcosy::Registry> registry)
{

}

void BulletSystem::unconfigure(std::shared_ptr<entcosy::Registry> registry)
{

}

void BulletSystem::update(std::shared_ptr<entcosy::Registry> registry, float deltaTime)
{
    registry->each<BulletTag, PositionComponent>([&](std::shared_ptr<entcosy::Entity> entity, BulletTag* bullet_tag,
        PositionComponent* position_component)
    {
        position_component->pos.x += 5;
        if(position_component->pos.x > getmaxx())
        {
            registry->destroy(entity);
        }
    });
}
