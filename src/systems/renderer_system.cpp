
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
    registry->each<PhysicsComponent, PolygonComponent>([&](ecs::Entity* entity, 
        ecs::ComponentHandle<PhysicsComponent> pc, ecs::ComponentHandle<PolygonComponent> vc) 
    {
        int bgiPoints[vc->points.size()*2];
        
        Vect2 centroid = vc->centroid + pc->rigid_body->position;
        float angle = pc->rigid_body->orient;
        PolygonCollider* collider = reinterpret_cast<PolygonCollider *>(pc->rigid_body->shape);
        float save;
        for(int i = 0; i < collider->m_vertexCount; i++) {
            Vect2 point = collider->m_vertices[i];
            Vect2 v = pc->rigid_body->position + pc->rigid_body->shape->u * point;
            bgiPoints[i*2] = v.x;
            bgiPoints[i*2+1] = v.y;
            // save = bgiPoints[i*2];
            // bgiPoints[i*2] = bgiPoints[i*2]*cos(angle) - bgiPoints[i*2+1]*sin(angle) + centroid.x - centroid.x*cos(angle) + centroid.y*sin(angle);
            // bgiPoints[i*2+1] = save*sin(angle) + bgiPoints[i*2+1]*cos(angle) + centroid.y - centroid.x*sin(angle) - centroid.y*cos(angle);
        }
        fillpoly(vc->points.size(), bgiPoints);
    });
}