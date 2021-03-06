#include "polygon_system.hpp"

PolygonSystem::~PolygonSystem()
{

}

void PolygonSystem::configure(std::shared_ptr<entcosy::Registry> registry)
{
    registry->subscribe<entcosy::events::OnComponentAssigned<PolygonComponent>>(this);
}

void PolygonSystem::unconfigure(std::shared_ptr<entcosy::Registry> registry)
{
    registry->unsubscribeAll(this);
}

void PolygonSystem::update(std::shared_ptr<entcosy::Registry> registry, float deltaTime)
{

}

void PolygonSystem::receive(std::shared_ptr<entcosy::Registry> registry, const entcosy::events::OnComponentAssigned<PolygonComponent>& event)
{
    PolygonComponent* pc = event.component;
    for(Vect2& point: pc->points)
    {
        point.x *= pc->scale;
        point.y *= pc->scale;
    }
    pc->centroid = _calculate_centroid(pc);
}

Vect2 PolygonSystem::_calculate_centroid(PolygonComponent* pc)
{
    Vect2 centroid = {0, 0};
    float signedArea = 0.0;
    float x0 = 0.0; // Current vertex X
    float y0 = 0.0; // Current vertex Y
    float x1 = 0.0; // Next vertex X
    float y1 = 0.0; // Next vertex Y
    float a = 0.0;  // Partial signed area

    // For all vertices except last
    int i=0;
    for (i=0; i < pc->points.size() - 1; ++i)
    {
        x0 = pc->points.at(i).x;
        y0 = pc->points.at(i).y;
        x1 = pc->points.at(i+1).x;
        y1 = pc->points.at(i+1).y;
        a = x0*y1 - x1*y0;
        signedArea += a;
        centroid.x += (x0 + x1)*a;
        centroid.y += (y0 + y1)*a;
    }

    // Do last vertex separately to avoid performing an expensive
    // modulus operation in each iteration.
    x0 = pc->points.at(i).x;
    y0 = pc->points.at(i).y;
    x1 = pc->points.at(0).x;
    y1 = pc->points.at(0).y;
    a = x0*y1 - x1*y0;
    signedArea += a;
    centroid.x += (x0 + x1)*a;
    centroid.y += (y0 + y1)*a;

    signedArea *= 0.5;
    centroid.x /= (6.0*signedArea);
    centroid.y /= (6.0*signedArea);

    return centroid;
}

