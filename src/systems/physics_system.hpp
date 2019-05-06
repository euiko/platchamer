#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"
#include "../core/physics/ecs/manifold.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../components/circle_collider_component.hpp"
#include "../components/rigid_body_component.hpp"

class PhysicsSystem: public entcosy::System,
    public entcosy::EventSubscriber<entcosy::events::OnComponentAssigned<PolygonColliderComponent>>,
    public entcosy::EventSubscriber<entcosy::events::OnComponentAssigned<CircleColliderComponent>>,
    public entcosy::EventSubscriber<entcosy::events::OnComponentAssigned<RigidBodyComponent>>
{
public:

	const Vect2 gravity;

	PhysicsSystem(const float& gravity_scale = 5.0f);

	virtual ~PhysicsSystem();

	virtual void configure(std::shared_ptr<entcosy::Registry> registry) override;

	virtual void unconfigure(std::shared_ptr<entcosy::Registry> registry) override;

	virtual void update(std::shared_ptr<entcosy::Registry> registry, float deltaTime) override;

	virtual void receive(std::shared_ptr<entcosy::Registry> registry, const entcosy::events::OnComponentAssigned<PolygonColliderComponent>& event) override;
	virtual void receive(std::shared_ptr<entcosy::Registry> registry, const entcosy::events::OnComponentAssigned<CircleColliderComponent>& event) override;
	virtual void receive(std::shared_ptr<entcosy::Registry> registry, const entcosy::events::OnComponentAssigned<RigidBodyComponent>& event) override;

private:
	// void applyImpulse(const ComponentHandle<PolygonColliderComponent>& physicsComponent, const Vect2& impulse, const Vect2& contact_vector);

	// void applyForce(const ComponentHandle<PolygonColliderComponent>& physicsComponent, const Vect2& f );

	template<typename T>
	void solveCollision( std::shared_ptr<entcosy::Registry> registry );

	void integrateForces( RigidBodyComponent* rigid_body, float dt );

	void integrateVelocity( std::shared_ptr<entcosy::Entity> entity, float dt );

	void setOrient(std::shared_ptr<entcosy::Entity> entity, float radians );


private:
	float m_dt = 1.0f / 60.0f;
	uint32_t m_iterations = 10;
	// std::vector<std::shared_ptr<entcosy::Entity>> bodies;
	std::vector<physics::ecs::Manifold> contacts;
};

#endif
