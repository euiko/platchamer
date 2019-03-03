#include "factories.hpp"

#include "../types/vect2.hpp"
#include "../components/position_component.hpp"
#include "../components/polygon_component.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/player_tag.hpp"
#include "../tags/bullet_tag.hpp"

ecs::Entity* makePlayer(ecs::Registry* registry) 
{
    ecs::Entity* player = registry->create();
    player->assign<PositionComponent>(0, 0, 0.0f);
    //Kotak biasa
    std::vector<Vect2> shape = {
        {109.58, 54.65},
        {93.19, 49.34},
        {73.09, 47.51},
        {60.30, 43.86},
        {56.65, 43.86},
        {39.91, 23.76},
        {43.85, 23.76},
        {46.42, 23.50},
        {47.51, 22.84},
        {46.42, 22.18},
        {43.85, 21.93},
        {38.37, 21.93},
        {29.24, 21.93},
        {25.58, 21.93},
        {25.58, 23.75},
        {29.24, 23.75},
        {29.24, 47.51},
        {20.10, 47.51},
        {9.14, 34.72},
        {3.65, 34.72},
        {1.83, 36.55},
        {1.83, 47.51},
        {3.65, 47.51},
        {3.65, 49.34},
        {10.96, 49.34},
        {10.96, 49.79},
        {0.00, 51.16},
        {0.00, 58.47},
        {10.96, 59.84},
        {10.96, 60.30},
        {3.65, 60.30},
        {3.65, 62.13},
        {1.83, 62.13},
        {1.83, 73.09},
        {3.65, 74.92},
        {9.14, 74.92},
        {20.10, 62.13},
        {29.24, 62.13},
        {29.24, 85.88},
        {25.58, 85.88},
        {25.58, 87.71},
        {29.24, 87.71},
        {38.37, 87.71},
        {43.85, 87.71},
        {46.42, 87.45},
        {47.51, 86.79},
        {46.42, 86.14},
        {43.85, 85.88},
        {39.91, 85.88},
        {56.65, 65.78},
        {60.30, 65.78},
        {73.09, 62.13},
        {93.19, 60.30},
        {109.64, 54.82},
        {109.58, 54.65},
    };
    player->assign<PolygonComponent>(shape, 10, 1.0f);
    player->assign<PolygonColliderComponent>(shape.size(), shape, shape.size());
    player->assign<RigidBodyComponent>();
    player->assign<PlayerTag>();
    return player;
}


ecs::Entity* makeBullet(ecs::Registry* registry, ecs::Entity* player)
{
    ecs::Entity* bullet = registry->create();
    ecs::ComponentHandle<PositionComponent> pc = player->get<PositionComponent>();
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