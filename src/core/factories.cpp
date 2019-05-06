#include "factories.hpp"

#include "../types/vect2.hpp"
#include "../components/position_component.hpp"
#include "../components/camera_component.hpp"
#include "../components/polygon_component.hpp"
#include "../components/circle_component.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../components/circle_collider_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/camera_tag.hpp"
#include "../tags/ground_tag.hpp"
#include "../tags/player_tag.hpp"
#include "../tags/enemy_tag.hpp"
#include "../tags/bullet_tag.hpp"

std::shared_ptr<entcosy::Entity> makePlayer(std::shared_ptr<entcosy::Registry> registry, float x, float y)
{
    std::shared_ptr<entcosy::Entity> player = registry->create();
    player->assign<PositionComponent>(x, y, 0.0f);
    //Kotak biasa
    std::vector<Vect2> shape = {
        {0, 0},
        {30, 0},
        {30, 60},
        {0, 60},
    };
    std::vector<Vect2> circleShape;

    float radius = 25;
    const uint32_t k_segments = 10;

    float theta = 0.0f;
    float inc = M_PI * 2.0f / (float)k_segments;
    Vect2 pos = {x,y};
    for(uint64_t i = 0; i < k_segments; ++i)
    {
        theta += inc;
        Vect2 p( std::cos( theta ), std::sin( theta ) );
        p *= radius;
        // p += pos;
        circleShape.push_back(p);
    }
    player->assign<PolygonComponent>(circleShape, 15, 1.0f);
    // player->assign<PolygonColliderComponent>(circleShape);
    player->assign<CircleColliderComponent>(radius);
    player->assign<RigidBodyComponent>(3.0f, 7.0f, 5.0f, 5.0f);
    player->assign<PlayerTag>();

    return player;
}


std::shared_ptr<entcosy::Entity> makeBullet(std::shared_ptr<entcosy::Registry> registry, std::shared_ptr<entcosy::Entity> player)
{
    std::shared_ptr<entcosy::Entity> bullet = registry->create();
    PositionComponent* pc = player->get<PositionComponent>();
    bullet->assign<PositionComponent>(pc->pos.x, pc->pos.y, 0.0f);
    std::vector<Vect2> shape = {
        {75, 50},
        {85, 50},
        {85, 55},
        {75, 55},
    };
    bullet->assign<PolygonComponent>(shape, 15, 1.0f);
    bullet->assign<BulletTag>();
    return bullet;
}

std::shared_ptr<entcosy::Entity> makeBlock(std::shared_ptr<entcosy::Registry> registry, float x, float y, float rotation)
{
    std::shared_ptr<entcosy::Entity> block = registry->create();
    block->assign<GroundTag>();
    block->assign<PositionComponent>(x, y, rotation);
    std::vector<Vect2> shape = {
        {0, 0},
        {800, 0},
        {800, 20},
        {0, 20},
    };
    block->assign<PolygonComponent>(shape, 15, 1.0f);
    block->assign<PolygonColliderComponent>(shape);
    block->assign<RigidBodyComponent>(true);
    return block;
}

std::shared_ptr<entcosy::Entity> makeEnemy(std::shared_ptr<entcosy::Registry> registry, float x, float y)
{
    std::shared_ptr<entcosy::Entity> enemy = registry->create();
    enemy->assign<PositionComponent>(x, y, 0.0f);
    std::vector<Vect2> shape = {
        {0, 0},
        {80, 0},
        {80, 80},
        {0, 80},
    };
    enemy->assign<PolygonComponent>(shape, 14, 1.0f);
    enemy->assign<PolygonColliderComponent>(shape);
    enemy->assign<RigidBodyComponent>(1.0f, 0.7, 0.5f, 0.1f);
    enemy->assign<EnemyTag>();
    return enemy;
}


std::shared_ptr<entcosy::Entity> makeCamera(std::shared_ptr<entcosy::Registry> registry, std::shared_ptr<entcosy::Entity> looked_object)
{
    std::shared_ptr<entcosy::Entity> camera = registry->create();
    camera->assign<CameraTag>();
    camera->assign<PositionComponent>(0.0f,0.0f,0.0f);
    camera->assign<CameraComponent>(looked_object);
    return camera;
}
