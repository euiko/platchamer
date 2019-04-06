#ifndef POLYGON_SYSTEM_HPP
#define POLYGON_SYSTEM_HPP
#include "../core/ecs.hpp"
#include "../components/polygon_component.hpp"

using namespace ecs;
class PolygonSystem : public EntitySystem,
	public EventSubscriber<events::OnComponentAssigned<PolygonComponent>>
{
public:
	virtual ~PolygonSystem();

	virtual void configure(Registry* registry) override;

	virtual void unconfigure(Registry* registry) override;

	virtual void tick(Registry* registry, float deltaTime) override;

	virtual void receive(Registry* registry, const events::OnComponentAssigned<PolygonComponent>& event) override;

private:
    Vect2 _calculate_centroid(ComponentHandle<PolygonComponent> pc);

};

#endif