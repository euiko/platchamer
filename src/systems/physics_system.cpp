#include "physics_system.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../core/physics/ecs/rigid_body.hpp"
#include "../tags/enemy_tag.hpp"

PhysicsSystem::PhysicsSystem(const float& gravity_scale) : gravity( 0, 10.0f * gravity_scale )
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
    size_t count = 0;
    for(auto colliderEntity: registry->each<PolygonColliderComponent>())
    {
        ComponentHandle<PolygonColliderComponent> polygonColliderA = colliderEntity->get<PolygonColliderComponent>();
        auto colliderEntites = registry->each<PolygonColliderComponent>();
        if(colliderEntites.begin() + count  == colliderEntites.end())
            break;
        // auto anotherColliderEntityIteration = colliderEntites.begin() + 1;
        for (auto anotherColliderEntityIteration = colliderEntites.begin() + 1; 
            anotherColliderEntityIteration != colliderEntites.end(); 
            ++anotherColliderEntityIteration
        ){
            auto anotherColliderEntity = anotherColliderEntityIteration.get();

            if(colliderEntity->get<RigidBodyComponent>()->inverse_mass == 0 
                && anotherColliderEntity->get<RigidBodyComponent>()->inverse_mass == 0)
                    continue;
            physics::ecs::Manifold m( colliderEntity, anotherColliderEntity, gravity );
            m.solve( );
            if(m.contact_count)
                contacts.emplace_back( m );
        };
        count++;
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
    ComponentHandle<RigidBodyComponent> rigid_body = event.component;
    ComponentHandle<PositionComponent> positionComponent = event.entity->get<PositionComponent>();

    physics::ecs::computePolygonMass(event.entity, rigid_body->density);

    rigid_body->velocity = {0, 0};
    rigid_body->angular_velocity = 0;
    rigid_body->torque = 0;
    rigid_body->force = { 0, 0 };
    if(rigid_body->static_friction == 0)
        rigid_body->static_friction = 1.5f;
    if(rigid_body->dynamic_friction == 0)
        rigid_body->dynamic_friction = 0.7f;
    if(rigid_body->restitution == 0.0f)
        rigid_body->restitution = 0.2f;
    if(positionComponent.isValid())
        setOrient( event.entity, positionComponent->rotation );
    if (rigid_body->is_static)
    {
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

void PhysicsSystem::setOrient(Entity* entity, float radians )
{
    ComponentHandle<RigidBodyComponent> rigidBody = entity->get<RigidBodyComponent>();
    rigidBody->orient = radians;
    if(entity->has<PolygonColliderComponent>())
    {
        ComponentHandle<PolygonColliderComponent> polygonCollider = entity->get<PolygonColliderComponent>();
        polygonCollider->orientation_matrix = { radians };
    }
}