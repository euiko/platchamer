
#include <vector>
extern "C" {
    #include <sdl_bgi/graphics.h>
}
#include "renderer_system.hpp"
#include "../components/position_component.hpp"
#include "../components/physics_component.hpp"
#include "../components/polygon_component.hpp"

void RendererSystem::render(Window* window, ecs::Registry* registry)
{
    registry->each<PhysicsComponent, PolygonComponent>([&](ecs::Entity* entity, 
        ecs::ComponentHandle<PhysicsComponent> pc, ecs::ComponentHandle<PolygonComponent> vc) 
    {
        int bgiPoints[vc->points.size()*2];
        int i = 0;
        Vect2 centroid = vc->centroid + pc->rigid_body.position;
        float angle = pc->rigid_body.orient;
        float save;
        for(Vect2& point: vc->points) {
            
            bgiPoints[i*2] = point.x + pc->rigid_body.position.x;
            bgiPoints[i*2+1] = point.y + pc->rigid_body.position.y;
            save = bgiPoints[i*2];
            bgiPoints[i*2] = bgiPoints[i*2]*cos(angle) - bgiPoints[i*2+1]*sin(angle) + centroid.x - centroid.x*cos(angle) + centroid.y*sin(angle);
            bgiPoints[i*2+1] = save*sin(angle) + bgiPoints[i*2+1]*cos(angle) + centroid.y - centroid.x*sin(angle) - centroid.y*cos(angle);
            i++;
        }
        fillpoly(vc->points.size(), bgiPoints);
    });
}