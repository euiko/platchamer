extern "C" {
    #include <sdl_bgi/graphics.h>
}

#include "player_control_system.hpp"
#include "../core/factories.hpp"
#include "../components/position_component.hpp"
#include "../components/rigid_body_component.hpp"
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
    registry->each<PlayerTag, RigidBodyComponent>(
        [&](Entity* entity, ComponentHandle<PlayerTag> player_tag, 
            ComponentHandle<RigidBodyComponent> rigid_body)
        {
            if(event.keycode ==  SDLK_w)
                rigid_body->velocity.y = -100.0f;
                // position_component->pos.y -= 20;
            if(event.keycode == SDLK_a)
                rigid_body->velocity.x -= 20.0f;
            if(event.keycode == SDLK_s)
                rigid_body->velocity.y += 25.0f;
            if(event.keycode == SDLK_d)
                rigid_body->velocity.x += 20.0f;
            if(event.keycode == SDLK_SPACE)
                makeBullet(registry, entity);
                   
        }
    );
}
