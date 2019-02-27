
#include <vector>
extern "C" {
    #include <sdl_bgi/graphics.h>
}
#include "renderer_system.hpp"
#include "../components/position_component.hpp"
#include "../components/physics_component.hpp"
#include "../components/polygon_component.hpp"
#include "../core/physics/shapes/polygon_collider.hpp"

void RendererSystem::render(Window* window, ecs::Registry* registry)
{
    registry->each<PositionComponent, PolygonComponent>([&](ecs::Entity* entity, 
        ecs::ComponentHandle<PositionComponent> pc, ecs::ComponentHandle<PolygonComponent> vc) 
    {
        int bgiPoints[vc->points.size()*2];
        int i = 0;
        Vect2 centroid = vc->centroid + pc->pos;
        float angle = pc->rotation * M_PI/180;
        float save;
        setfillstyle(SOLID_FILL, vc->color);
        setcolor(vc->color);
        for(Vect2& point: vc->points) {
            
            bgiPoints[i*2] = point.x + pc->pos.x;
            bgiPoints[i*2+1] = point.y + pc->pos.y;
            save = bgiPoints[i*2];
            bgiPoints[i*2] = bgiPoints[i*2]*cos(angle) - bgiPoints[i*2+1]*sin(angle) + centroid.x - centroid.x*cos(angle) + centroid.y*sin(angle);
            bgiPoints[i*2+1] = save*sin(angle) + bgiPoints[i*2+1]*cos(angle) + centroid.y - centroid.x*sin(angle) - centroid.y*cos(angle);
            i++;
        }
        fillpoly(vc->points.size(), bgiPoints);
    });
}