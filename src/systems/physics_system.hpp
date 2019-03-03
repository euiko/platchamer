#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "../core/ecs/registry.hpp"
#include "../core/physics/ecs/manifold.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../components/rigid_body_component.hpp"

using namespace ecs;
class PhysicsSystem: public EntitySystem,
    public EventSubscriber<events::OnComponentAssigned<PolygonColliderComponent>>,
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

	virtual void receive(Registry* registry, const events::OnComponentAssigned<PolygonColliderComponent>& event) override;
	virtual void receive(Registry* registry, const events::OnComponentAssigned<RigidBodyComponent>& event) override;
    
private:
	// void applyImpulse(const ComponentHandle<PolygonColliderComponent>& physicsComponent, const Vect2& impulse, const Vect2& contact_vector);

	// void applyForce(const ComponentHandle<PolygonColliderComponent>& physicsComponent, const Vect2& f );
	
	void integrateForces( ComponentHandle<RigidBodyComponent> rigid_body, float dt );
	
	void integrateVelocity( Entity *entity, float dt );

	void setOrient(Entity* entity, float radians );
	

private:
	float m_dt = 1.0f / 60.0f;
	uint32_t m_iterations = 10;
	std::vector<Entity *> bodies;
	std::vector<physics::ecs::Manifold> contacts;
};

#endif