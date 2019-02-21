#include "physics_system.hpp"


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::configure(Registry* registry)
{
    registry->subscribe<events::OnComponentAssigned<PhysicsComponent>>(this);
}

void PhysicsSystem::unconfigure(Registry* registry)
{
    registry->unsubscribeAll(this);
}

void PhysicsSystem::tick(Registry* registry, float deltaTime)
{

}

void PhysicsSystem::receive(Registry* registry, const events::OnComponentAssigned<PhysicsComponent>& event)
{
    ComponentHandle<PhysicsComponent> physicsComponent = event.component;
    if (physicsComponent->is_static)
    {
        physicsComponent->inertia = 0.0f;
        physicsComponent->inverse_inertia = 0.0f;
        physicsComponent->mass = 0.0f;
        physicsComponent->inverse_mass = 0.0f;
    }
    
}

void PhysicsSystem::applyImpulse(const ComponentHandle<PhysicsComponent>& physicsComponent, const Vect2& impulse, const Vect2& contact_vector )
{
    physicsComponent->velocity += physicsComponent->inverse_mass * impulse;
    physicsComponent->angular_velocity += physicsComponent->inverse_inertia * contact_vector.cross(impulse);
}


void PhysicsSystem::applyForce(const ComponentHandle<PhysicsComponent>& physicsComponent, const Vect2& f )
{
    physicsComponent->force += f;
}