extern "C" {
    #include <sdl_bgi/graphics.h>
}

#include "player_control_system.hpp"
#include "../core/game.hpp"
#include "../core/factories.hpp"
#include "../components/position_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../components/ui/game_ui_component.hpp"
#include "../tags/player_tag.hpp"
#include "../tags/ground_tag.hpp"
#include "../tags/thorn_tag.hpp"

PlayerControlSystem::~PlayerControlSystem()
{

}

void PlayerControlSystem::configure(std::shared_ptr<entcosy::Registry> registry)
{
    registry->subscribe<ResetPlayerStateEvent>(this);
    registry->subscribe<KeyboardEvent>(this);
    registry->subscribe<CollideEvent>(this);
}

void PlayerControlSystem::unconfigure(std::shared_ptr<entcosy::Registry> registry)
{
    registry->unsubscribeAll(this);
}

void PlayerControlSystem::update(std::shared_ptr<entcosy::Registry> registry, float deltaTime)
{
    const Uint8 *keyboards = SDL_GetKeyboardState(NULL);
    registry->each<PlayerTag, RigidBodyComponent>(
        [&](std::shared_ptr<entcosy::Entity> entity, PlayerTag* playerTag,
            RigidBodyComponent* rigidBody)
        {
            if(keyboards[SDL_SCANCODE_W] && playerTag->is_ground)
                rigidBody->velocity.y = -300.0f;
                // position_component->pos.y -= 20;
            if(keyboards[SDL_SCANCODE_A] && rigidBody->velocity.x > -200.0f)
                rigidBody->velocity.x -= 10.0f;
            if(keyboards[SDL_SCANCODE_D] && rigidBody->velocity.y < 200.0f)
                rigidBody->velocity.x += 10.0f;
            // std::cout << playerTag->is_ground << " = ";
            // if(rigidBody->velocity.y < -200.0f) rigidBody->velocity.y = -200.0f;
            // if(rigidBody->velocity.x > 200.0f) rigidBody->velocity.y = 200.0f;
            // if(rigidBody->velocity.x < -200.0f) rigidBody->velocity.y = 200.0f;


            // if(rigidBody->velocity.x > 0)
            //     rigidBody->velocity.x -= 2;
            // if(rigidBody->velocity.x < 0)
            //     rigidBody->velocity.x += 2;

            if(keyboards[SDLK_SPACE])
                makeBullet(registry, entity);

        }
    );
}

void PlayerControlSystem::receive(std::shared_ptr<entcosy::Registry> registry, const KeyboardEvent& event)
{

}


void PlayerControlSystem::receive(std::shared_ptr<entcosy::Registry> registry, const CollideEvent& event)
{
    if(
        (event.entityA->has<PlayerTag>() && event.entityB->has<GroundTag>()) ||
        (event.entityB->has<PlayerTag>() && event.entityA->has<GroundTag>())
    )
    {
        registry->each<PlayerTag>([&](std::shared_ptr<entcosy::Entity> entity, PlayerTag *playerTag)
        {
            playerTag->is_ground = playerTag->is_ground || event.isCollide;
            // std::cout << playerTag->is_ground << " ";
        });
    }
    if(
        (event.entityA->has<PlayerTag>() && event.entityB->has<ThornTag>()) ||
        (event.entityB->has<PlayerTag>() && event.entityA->has<ThornTag>())
    )
    {
        std::cout << event.isCollide << "\n";
        if(event.isCollide)
            registry->changeUi<GameUiComponent>();
    }
}


void PlayerControlSystem::receive(std::shared_ptr<entcosy::Registry> registry, const ResetPlayerStateEvent& event)
{
    // std::cout << "\n===================================\n";
    registry->each<PlayerTag>([&](std::shared_ptr<entcosy::Entity> entity, PlayerTag *playerTag)
    {
        playerTag->is_ground = 0;
    });
}
