#include "physics_system.hpp"

PhysicsSystem::PhysicsSystem() : gravity( 0, 10.0f * gravityScale )
{

}

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
    contacts.clear( );
    auto entityIter = registry->each<PhysicsComponent>();
    size_t count = 0;
    for(auto ent: entityIter)
    {
        count++;
        ComponentHandle<PhysicsComponent> pcA = ent->get<PhysicsComponent>();
        RigidBody *A = &pcA->rigid_body;

        for(auto nextEnttIter = entityIter.begin() + count; nextEnttIter != entityIter.end(); ++nextEnttIter)
        {
            auto nextEntt = nextEnttIter.get();
            ComponentHandle<PhysicsComponent> pcB = nextEntt->get<PhysicsComponent>();
            RigidBody *B = &pcB->rigid_body;

            if(A->im == 0 && B->im == 0)
                continue;
            Manifold m( A, B );
            m.Solve( );
            if(m.contact_count)
                contacts.emplace_back( m );
        }
    }

    // Integrate forces
    for(auto ent: registry->each<PhysicsComponent>())
        integrateForces( &ent->get<PhysicsComponent>().get().rigid_body, m_dt );

    // Initialize collision
    for(uint32_t i = 0; i < contacts.size( ); ++i)
        contacts[i].Initialize( );

    // Solve collisions
    for(uint32_t j = 0; j < m_iterations; ++j)
        for(uint32_t i = 0; i < contacts.size( ); ++i)
        contacts[i].ApplyImpulse( );

    // Integrate velocities
    for(auto ent: registry->each<PhysicsComponent>())
        integrateVelocity( &ent->get<PhysicsComponent>().get().rigid_body, m_dt );

    // Correct positions
    for(uint32_t i = 0; i < contacts.size( ); ++i)
        contacts[i].PositionalCorrection( );

    // Clear all forces
    for(auto ent: registry->each<PhysicsComponent>())
    {
        ComponentHandle<PhysicsComponent> pcB = ent->get<PhysicsComponent>();
        RigidBody *b = &pcB->rigid_body;
        b->force= { 0, 0 };
        b->torque = 0;
    }
}

void PhysicsSystem::receive(Registry* registry, const events::OnComponentAssigned<PhysicsComponent>& event)
{
    ComponentHandle<PhysicsComponent> physicsComponent = event.component;
    physicsComponent->rigid_body.SetOrient( generateRandom( -M_PI, M_PI ) );
    physicsComponent->rigid_body.restitution = 0.2f;
    physicsComponent->rigid_body.dynamic_friction = 0.2f;
    physicsComponent->rigid_body.static_friction = 0.4f;
    // if (physicsComponent->is_static)
    // {
    //     physicsComponent->inertia = 0.0f;
    //     physicsComponent->inverse_inertia = 0.0f;
    //     physicsComponent->mass = 0.0f;
    //     physicsComponent->inverse_mass = 0.0f;
    // }
    
}

void PhysicsSystem::integrateForces( RigidBody *b, float dt )
{
    if(b->im == 0.0f)
        return;

    b->velocity += (b->force * b->im + gravity) * (dt / 2.0f);
    b->angular_velocity += b->torque * b->iI * (dt / 2.0f);
}

void PhysicsSystem::integrateVelocity( RigidBody *b, float dt )
{
    if(b->im == 0.0f)
        return;

    b->position += b->velocity * dt;
    b->orient += b->angular_velocity * dt;
    b->SetOrient( b->orient );
    integrateForces( b, dt );
}

void PhysicsSystem::applyImpulse(const ComponentHandle<PhysicsComponent>& physicsComponent, const Vect2& impulse, const Vect2& contact_vector )
{
    // physicsComponent->velocity += physicsComponent->inverse_mass * impulse;
    // physicsComponent->angular_velocity += physicsComponent->inverse_inertia * contact_vector.cross(impulse);
}


void PhysicsSystem::applyForce(const ComponentHandle<PhysicsComponent>& physicsComponent, const Vect2& f )
{
    // physicsComponent->force += f;
}