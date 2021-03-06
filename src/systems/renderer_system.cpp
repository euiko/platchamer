
#include <vector>
extern "C" {
    #include <sdl_bgi/graphics.h>
}
#include "renderer_system.hpp"
#include "../components/position_component.hpp"
#include "../components/camera_component.hpp"
#include "../components/circle_collider_component.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../components/polygon_component.hpp"
#include "../components/circle_component.hpp"
#include "../tags/camera_tag.hpp"
#include "../tags/player_tag.hpp"

void RendererSystem::render(platchamer::graphics::Window* window, std::shared_ptr<entcosy::Registry> registry)
{
    registry->each<PositionComponent, PolygonComponent>([&](std::shared_ptr<entcosy::Entity> entity,
        PositionComponent* pc, PolygonComponent* vc)
    {
        setfillstyle(SOLID_FILL, vc->color);
        int bgiPoints[vc->points.size()*2];
        int i = 0;
        Collider* collider;
        if(entity->has<PolygonColliderComponent>())
        {
            collider = entity->get<PolygonColliderComponent>();
        } else if (entity->has<CircleColliderComponent>())
        {
            collider = entity->get<CircleColliderComponent>();
        }
        PositionComponent* cameraPosition;
        registry->each<CameraTag>([&](std::shared_ptr<entcosy::Entity> cameraEntity, CameraTag* cameraTag)
        {
            cameraPosition = cameraEntity->get<PositionComponent>();
        });

        setcolor(vc->color);
        for(Vect2& point: vc->points) {
            Vect2 v = point;
            if(collider != nullptr)
            {
                v = collider->orientation_matrix * point;
            }
            if(cameraPosition != nullptr)
            {
                v = cameraPosition->pos + v;
            }
            v = pc->pos + v;
            bgiPoints[i*2] = v.x;
            bgiPoints[i*2+1] = v.y;
            // save = bgiPoints[i*2];
            // bgiPoints[i*2] = bgiPoints[i*2]*cos(angle) - bgiPoints[i*2+1]*sin(angle) + centroid.x - centroid.x*cos(angle) + centroid.y*sin(angle);
            // bgiPoints[i*2+1] = save*sin(angle) + bgiPoints[i*2+1]*cos(angle) + centroid.y - centroid.x*sin(angle) - centroid.y*cos(angle);
            i++;
        }
        fillpoly(vc->points.size(), bgiPoints);
    });


    registry->each<PositionComponent, CircleComponent>([&](std::shared_ptr<entcosy::Entity> entity,
        PositionComponent* positionComponent, CircleComponent* circleComponent)
    {
        setfillstyle(SOLID_FILL, circleComponent->color);
        circle(positionComponent->pos.x * circleComponent->scale ,
            positionComponent->pos.y * circleComponent->scale, circleComponent->radius);
    });
}
