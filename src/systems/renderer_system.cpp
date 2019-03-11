
#include <vector>
extern "C" {
    #include <sdl_bgi/graphics.h>
}
#include "renderer_system.hpp"
#include "../components/position_component.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../components/polygon_component.hpp"

void RendererSystem::render(platchamer::graphics::Window* window, ecs::Registry* registry)
{
    registry->each<PositionComponent, PolygonComponent>([&](ecs::Entity* entity, 
        ecs::ComponentHandle<PositionComponent> pc, ecs::ComponentHandle<PolygonComponent> vc) 
    {
        int bgiPoints[vc->points.size()*2];
        int i = 0;
        ecs::ComponentHandle<PolygonColliderComponent> polygonCollider = entity->get<PolygonColliderComponent>();
        setfillstyle(SOLID_FILL, vc->color);
        setcolor(vc->color);
        for(Vect2& point: vc->points) {
            Vect2 v = point;
            if(polygonCollider.isValid())
            {
                v = polygonCollider->orientation_matrix * point;
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
}