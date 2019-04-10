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
    const Uint8 *keyboards = SDL_GetKeyboardState(NULL);
    registry->each<PlayerTag, RigidBodyComponent>(
        [&](Entity* entity, ComponentHandle<PlayerTag> player_tag, 
            ComponentHandle<RigidBodyComponent> rigid_body)
        {
            if(keyboards[SDL_SCANCODE_W])
                rigid_body->velocity.y = -300.0f;
                // position_component->pos.y -= 20;
            if(keyboards[SDL_SCANCODE_A] && rigid_body->velocity.x > -200.0f)
                rigid_body->velocity.x -= 10.0f;
            if(keyboards[SDL_SCANCODE_D] && rigid_body->velocity.y < 200.0f)
                rigid_body->velocity.x += 10.0f;
            // if(rigid_body->velocity.y < -200.0f) rigid_body->velocity.y = -200.0f; 
            // if(rigid_body->velocity.x > 200.0f) rigid_body->velocity.y = 200.0f; 
            // if(rigid_body->velocity.x < -200.0f) rigid_body->velocity.y = 200.0f; 


            // if(rigid_body->velocity.x > 0)
            //     rigid_body->velocity.x -= 2;
            // if(rigid_body->velocity.x < 0)
            //     rigid_body->velocity.x += 2;
                
            if(keyboards[SDLK_SPACE])
                makeBullet(registry, entity);
                   
        }
    );
}

void PlayerControlSystem::receive(entcosy::Registry* registry, const KeyboardEvent& event)
{
}
