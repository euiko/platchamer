#include "physics_system.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../core/physics/ecs/rigid_body.hpp"
#include "../events/collide_event.hpp"
#include "../tags/enemy_tag.hpp"
#include "../types/collider_entity.hpp"

PhysicsSystem::PhysicsSystem(const float& gravity_scale) : gravity( 0, 10.0f * gravity_scale )
{
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::configure(entcosy::Registry* registry)
{
    registry->subscribe<entcosy::events::OnComponentAssigned<PolygonColliderComponent>>(this);
    registry->subscribe<entcosy::events::OnComponentAssigned<RigidBodyComponent>>(this);
    registry->subscribe<entcosy::events::OnComponentAssigned<CircleColliderComponent>>(this);
}

void PhysicsSystem::unconfigure(entcosy::Registry* registry)
{
    registry->unsubscribeAll(this);
}

void PhysicsSystem::update(entcosy::Registry* registry, float deltaTime)
{
    contacts.clear( );
    size_t count = 0;
    std::vector<ColliderEntity> colliderEntities;
    for(auto colliderEntity: registry->each<PolygonColliderComponent>())
    {
        colliderEntities.push_back({ colliderEntity, colliderEntity->get<PolygonColliderComponent>() });
    }
    for(auto colliderEntity: registry->each<CircleColliderComponent>())
    {
        colliderEntities.push_back({ colliderEntity, colliderEntity->get<CircleColliderComponent>() });
    }
    for(auto& colliderEntity: colliderEntities)
    {
        // auto colliderEntites = registry->each<PolygonColliderComponent>();
        if(colliderEntities.begin() + count  == colliderEntities.end())
            break;

        for (auto entityIdIterator = colliderEntities.begin() + 1; 
            entityIdIterator != colliderEntities.end(); 
            ++entityIdIterator
        ){
            ColliderEntity anotherColliderEntity = *entityIdIterator;

            if(colliderEntity.entity->get<RigidBodyComponent>()->inverse_mass == 0 
                && anotherColliderEntity.entity->get<RigidBodyComponent>()->inverse_mass == 0)
                    continue;
            physics::ecs::Manifold m( colliderEntity.entity, anotherColliderEntity.entity, gravity );
            m.solve( colliderEntity.collider, anotherColliderEntity.collider );
            if(m.contact_count) 
            {
                contacts.emplace_back( m );
                registry->emit<CollideEvent>({colliderEntity.entity, anotherColliderEntity.entity, true});
            }else
            {
                registry->emit<CollideEvent>({colliderEntity.entity, anotherColliderEntity.entity, false});
            }
            
                
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
    for(auto& ColliderEntity: colliderEntities)
    {
        integrateVelocity( ColliderEntity.entity, m_dt );
    }

    // Correct positions
    for(uint32_t i = 0; i < contacts.size( ); ++i)
        contacts[i].positionalCorrection( );

    // Clear all forces
    for(auto entity: registry->each<RigidBodyComponent>())
    {
        RigidBodyComponent* rigidBodyB = entity->get<RigidBodyComponent>();
        rigidBodyB->force= { 0, 0 };
        rigidBodyB->torque = 0;
    }
}

void PhysicsSystem::receive(entcosy::Registry* registry, const entcosy::events::OnComponentAssigned<PolygonColliderComponent>& event)
{
    physics::ecs::initPolygonVertices(event.entity);    
    physics::ecs::computePolygonMass(event.entity, 1.0f);
}

void PhysicsSystem::receive(entcosy::Registry* registry, const entcosy::events::OnComponentAssigned<CircleColliderComponent>& event)
{
    physics::ecs::computeCircleMass(event.entity, 1.0f);
}

void PhysicsSystem::receive(entcosy::Registry* registry, const entcosy::events::OnComponentAssigned<RigidBodyComponent>& event)
{
    RigidBodyComponent* rigid_body = event.component;
    PositionComponent* positionComponent = event.entity->get<PositionComponent>();
    
    Collider collider;
    if(event.entity->has<PolygonColliderComponent>())
        collider = { event.entity->get<PolygonColliderComponent>()->colliderType };
    
    if(event.entity->has<CircleColliderComponent>())
        collider = { event.entity->get<CircleColliderComponent>()->colliderType };

    physics::ecs::ComputeMass[collider.colliderType](event.entity, rigid_body->density);

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
    if(positionComponent != nullptr)
        setOrient( event.entity, positionComponent->rotation );
    if (rigid_body->is_static)
    {
        rigid_body->inertia = 0.0f;
        rigid_body->inverse_inertia = 0.0f;
        rigid_body->mass = 0.0f;
        rigid_body->inverse_mass = 0.0f;
    }
}

void PhysicsSystem::integrateForces( RigidBodyComponent* rigid_body, float dt )
{
    if(rigid_body->inverse_mass == 0.0f)
        return;
    rigid_body->velocity += (rigid_body->force * rigid_body->inverse_mass + gravity) * (dt / 2.0f);
    rigid_body->angular_velocity += rigid_body->torque * rigid_body->inverse_inertia * (dt / 2.0f);

}

void PhysicsSystem::integrateVelocity( std::shared_ptr<entcosy::Entity> entity, float dt )
{
    RigidBodyComponent* rigid_body = entity->get<RigidBodyComponent>();
    if(rigid_body->inverse_mass == 0.0f)
        return;

    PositionComponent* position = entity->get<PositionComponent>();
    position->pos += rigid_body->velocity * dt;
    rigid_body->orient += rigid_body->angular_velocity * dt;
    setOrient( entity, rigid_body->orient );
    integrateForces( rigid_body, dt );
}

void PhysicsSystem::setOrient(std::shared_ptr<entcosy::Entity> entity, float radians )
{
    RigidBodyComponent* rigidBody = entity->get<RigidBodyComponent>();
    rigidBody->orient = radians;
    Collider* collider;
    if(entity->has<PolygonColliderComponent>())
    {
        collider = entity->get<PolygonColliderComponent>();
    }
    else if(entity->has<CircleColliderComponent>())
    {
        collider = entity->get<CircleColliderComponent>();
    }

    collider->orientation_matrix = { radians };
}


template<typename T>
void PhysicsSystem::solveCollision( entcosy::Registry* registry)
{

}