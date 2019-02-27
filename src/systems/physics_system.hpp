#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "../core/ecs/registry.hpp"
#include "../core/physics/manifold.hpp"
#include "../components/physics_component.hpp"
#include "../components/rigid_body_component.hpp"

using namespace ecs;
class PhysicsSystem: public EntitySystem,
    public EventSubscriber<events::OnComponentAssigned<PhysicsComponent>>,
    public EventSubscriber<events::OnComponentAssigned<RigidBodyComponent>>
{
public:

	const float gravityScale = 5.0f;
	const Vect2 gravity;
	
	PhysicsSystem();

	virtual ~PhysicsSystem();

	virtual void configure(Registry* registry) override;

	virtual void unconfigure(Registry* registry) override;

	virtual void tick(Registry* registry, float deltaTime) override;

	virtual void receive(Registry* registry, const events::OnComponentAssigned<PhysicsComponent>& event) override;
	virtual void receive(Registry* registry, const events::OnComponentAssigned<RigidBodyComponent>& event) override;
    
private:
	void applyImpulse(const ComponentHandle<PhysicsComponent>& physicsComponent, const Vect2& impulse, const Vect2& contact_vector);

	void applyForce(const ComponentHandle<PhysicsComponent>& physicsComponent, const Vect2& f );
	
	void integrateForces( RigidBody *b, float dt );
	
	void integrateVelocity( RigidBody *b, float dt );
	
	void computeMass(Entity* entity, const ComponentHandle<RigidBodyComponent>& rigid_body );
	

private:
	float m_dt = 1.0f / 60.0f;
	uint32_t m_iterations = 10;
	std::vector<RigidBody *> bodies;
	std::vector<Manifold> contacts;
};

#endif