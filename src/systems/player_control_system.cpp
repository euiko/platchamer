extern "C" {
    #include <sdl_bgi/graphics.h>
}

#include "player_control_system.hpp"
#include "../core/factories.hpp"
#include "../components/position_component.hpp"
#include "../tags/player_tag.hpp"

PlayerControlSystem::~PlayerControlSystem()
{

}

void PlayerControlSystem::configure(Registry* registry) 
{
    registry->subscribe<KeyboardEvent>(this);    
}

void PlayerControlSystem::unconfigure(Registry* registry)
{
    registry->unsubscribeAll(this);
}

void PlayerControlSystem::tick(Registry* registry, float deltaTime)
{

}

void PlayerControlSystem::receive(Registry* registry, const KeyboardEvent& event)
{
    registry->each<PlayerTag, PositionComponent>(
        [&](Entity* entity, ComponentHandle<PlayerTag> player_tag, 
            ComponentHandle<PositionComponent> position_component)
        {
            if(event.keycode ==  SDLK_w)
                position_component->pos.y -= 20;
            if(event.keycode == SDLK_a)
                position_component->pos.x -= 20;
            if(event.keycode == SDLK_s)
                position_component->pos.y += 20;
            if(event.keycode == SDLK_d)
                position_component->pos.x += 20;
            if(event.keycode == SDLK_SPACE)
                makeBullet(registry, entity);
                   
        }
    );
}
