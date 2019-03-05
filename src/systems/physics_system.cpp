#include "physics_system.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../core/physics/ecs/rigid_body.hpp"

PhysicsSystem::PhysicsSystem() : gravity( 0, 10.0f * gravityScale )
{

}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::configure(Registry* registry)
{
    registry->subscribe<events::OnComponentAssigned<PolygonColliderComponent>>(this);
    registry->subscribe<events::OnComponentAssigned<RigidBodyComponent>>(this);
}

void PhysicsSystem::unconfigure(Registry* registry)
{
    registry->unsubscribeAll(this);
}

void PhysicsSystem::tick(Registry* registry, float deltaTime)
{
    contacts.clear( );
    auto colliderEntites = registry->each<PolygonColliderComponent>();
    size_t count = 0;
    for(auto colliderEntity: colliderEntites)
    {
        count++;
        ComponentHandle<PolygonColliderComponent> polygonColliderA = colliderEntity->get<PolygonColliderComponent>();

        for(auto anotherColliderEntityIteration = colliderEntites.begin() + count; anotherColliderEntityIteration != colliderEntites.end(); ++anotherColliderEntityIteration)
        {
            auto anotherColliderEntity = anotherColliderEntityIteration.get();

            if(colliderEntity->get<RigidBodyComponent>()->inverse_mass == 0 
                && anotherColliderEntity->get<RigidBodyComponent>()->inverse_mass == 0)
                continue;
            physics::ecs::Manifold m( colliderEntity, anotherColliderEntity );
            m.solve( );
            if(m.contact_count)
                contacts.emplace_back( m );
        }
    }

    // Integrate forces
    for(auto entity: registry->each<RigidBodyComponent>())
        integrateForces( entity->get<RigidBodyComponent>(), m_dt );

    // Initialize collision
    for(uint32_t i = 0; i < contacts.size( ); ++i)
        contacts[i].initialize( );

    // Solve collisions
    for(uint32_t j = 0; j < m_iterations; ++j)
        for(uint32_t i = 0; i < contacts.size( ); ++i)
        contacts[i].applyImpulse( );

    // Integrate velocities
    for(auto entity: registry->each<PolygonColliderComponent>())
        integrateVelocity( entity, m_dt );

    // Correct positions
    for(uint32_t i = 0; i < contacts.size( ); ++i)
        contacts[i].positionalCorrection( );

    // Clear all forces
    for(auto entity: registry->each<RigidBodyComponent>())
    {
        ComponentHandle<RigidBodyComponent> rigidBodyB = entity->get<RigidBodyComponent>();
        rigidBodyB->force= { 0, 0 };
        rigidBodyB->torque = 0;
    }
}

void PhysicsSystem::receive(Registry* registry, const events::OnComponentAssigned<PolygonColliderComponent>& event)
{
    physics::ecs::initPolygonVertices(event.entity);
    
    physics::ecs::computePolygonMass(event.entity, 1.0f);

}

void PhysicsSystem::receive(Registry* registry, const events::OnComponentAssigned<RigidBodyComponent>& event)
{
    physics::ecs::computePolygonMass(event.entity, 1.0f);
    
    ComponentHandle<RigidBodyComponent> rigid_body = event.component;

    // rigid_body->restitution = 0.2f;
    // rigid_body->dynamic_friction = 0.2f;
    // rigid_body->static_friction = 0.4f;

    rigid_body->velocity = {0, 0};
    rigid_body->angular_velocity = 0;
    rigid_body->torque = 0;
    rigid_body->force = { 0, 0 };
    rigid_body->static_friction = 0.5f;
    rigid_body->dynamic_friction = 0.3f;
    rigid_body->restitution = 0.2f;
    setOrient( event.entity, generateRandom( -M_PI, M_PI ) );
    if (rigid_body->is_static)
    {
        setOrient(event.entity, 0.0f);
        rigid_body->inertia = 0.0f;
        rigid_body->inverse_inertia = 0.0f;
        rigid_body->mass = 0.0f;
        rigid_body->inverse_mass = 0.0f;
    }
}

void PhysicsSystem::integrateForces( ComponentHandle<RigidBodyComponent> rigid_body, float dt )
{
    if(rigid_body->inverse_mass == 0.0f)
        return;

    rigid_body->velocity += (rigid_body->force * rigid_body->inverse_mass + gravity) * (dt / 2.0f);
    rigid_body->angular_velocity += rigid_body->torque * rigid_body->inverse_inertia * (dt / 2.0f);
}

void PhysicsSystem::integrateVelocity( Entity* entity, float dt )
{
    ComponentHandle<RigidBodyComponent> rigid_body = entity->get<RigidBodyComponent>();
    if(rigid_body->inverse_mass == 0.0f)
        return;

    ComponentHandle<PositionComponent> position = entity->get<PositionComponent>();
    position->pos += rigid_body->velocity * dt;
    rigid_body->orient += rigid_body->angular_velocity * dt;
    setOrient( entity, rigid_body->orient );
    integrateForces( rigid_body, dt );
}

// void PhysicsSystem::applyImpulse(const ComponentHandle<PolygonColliderComponent>& physicsComponent, const Vect2& impulse, const Vect2& contact_vector )
// {
//     // physicsComponent->velocity += physicsComponent->inverse_mass * impulse;
//     // physicsComponent->angular_velocity += physicsComponent->inverse_inertia * contact_vector.cross(impulse);
// }


// void PhysicsSystem::applyForce(const ComponentHandle<PolygonColliderComponent>& physicsComponent, const Vect2& f )
// {
//     // physicsComponent->force += f;
// }

void PhysicsSystem::setOrient(Entity* entity, float radians )
{
    ComponentHandle<RigidBodyComponent> rigid_body = entity->get<RigidBodyComponent>();
    rigid_body->orient = radians;
    if(entity->has<PolygonColliderComponent>())
    {
        ComponentHandle<PolygonColliderComponent> polygon_collider = entity->get<PolygonColliderComponent>();
        polygon_collider->orientation_matrix = { radians };
    }
}