#ifndef POLYGON_SYSTEM_HPP
#define POLYGON_SYSTEM_HPP
#include "../libs/entcosy/src/entcosy/registry.hpp"
#include "../components/polygon_component.hpp"

class PolygonSystem : public entcosy::System,
	public entcosy::EventSubscriber<entcosy::events::OnComponentAssigned<PolygonComponent>>
{
public:
	virtual ~PolygonSystem();

	virtual void configure(entcosy::Registry* registry) override;

	virtual void unconfigure(entcosy::Registry* registry) override;

	virtual void update(entcosy::Registry* registry, float deltaTime) override;

	virtual void receive(entcosy::Registry* registry, const entcosy::events::OnComponentAssigned<PolygonComponent>& event) override;

private:
    Vect2 _calculate_centroid(PolygonComponent* pc);

};

#endif