
#include <vector>
extern "C" {
    #include <sdl_bgi/graphics.h>
}
#include "renderer_system.hpp"
#include "../components/position_component.hpp"
#include "../components/vector_component.hpp"

void RendererSystem::render(Window* window, ecs::Registry* registry)
{
    registry->each<PositionComponent, VectorComponent>([&](ecs::Entity* entity, 
        ecs::ComponentHandle<PositionComponent> pc, ecs::ComponentHandle<VectorComponent> vc) 
    {
        int bgiPoints[vc->points.size()*2];
        int i = 0;        
        for(Vect2& point: vc->points) {
            
            bgiPoints[i*2] = point.x + pc->pos.x;
            bgiPoints[i*2+1] = point.y + pc->pos.y;
            i++;
        }
        fillpoly(vc->points.size(), bgiPoints);
    });
}