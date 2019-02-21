#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "../core/ecs/registry.hpp"
#include "../components/physics_component.hpp"

using namespace ecs;
class PhysicsSystem: public EntitySystem,
    public EventSubscriber<events::OnComponentAssigned<PhysicsComponent>>
{
public:
	virtual ~PhysicsSystem();

	virtual void configure(Registry* registry) override;

	virtual void unconfigure(Registry* registry) override;

	virtual void tick(Registry* registry, float deltaTime) override;

	virtual void receive(Registry* registry, const events::OnComponentAssigned<PhysicsComponent>& event) override;
    
private:
	void applyImpulse(const ComponentHandle<PhysicsComponent>& physicsComponent, const Vect2& impulse, const Vect2& contact_vector);

	void applyForce(const ComponentHandle<PhysicsComponent>& physicsComponent, const Vect2& f );
};

#endif