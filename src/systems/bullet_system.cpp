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

void BulletSystem::configure(Registry* registry) 
{
      
}

void BulletSystem::unconfigure(Registry* registry)
{
    
}

void BulletSystem::tick(Registry* registry, float deltaTime)
{
    registry->each<BulletTag, PositionComponent>([&](Entity* entity, ComponentHandle<BulletTag> bullet_tag, 
        ComponentHandle<PositionComponent> position_component)
    {
        position_component->pos.x += 5;
        if(position_component->pos.x > getmaxx()) 
        {
            registry->destroy(entity);
        }
    });
}