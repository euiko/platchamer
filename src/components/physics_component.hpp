#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP
#include <stdint.h>
#include "../types/shape.hpp"
#include "../types/vect2.hpp"

struct PhysicsComponent
{
  PhysicsComponent( float mass, float inertia, float staticFriction, float dynamicFriction, float restitution )
    : static_friction(staticFriction), dynamic_friction(dynamicFriction), restitution(restitution),
      torque(0), angularVelocity(0), velocity({0, 0})
  {

  }

  void ApplyForce( const Vect2& f )
  {
    force += f;
  }

  void ApplyImpulse( const Vect2& impulse, const Vect2& contactVector )
  {
    velocity += inverse_mass * impulse;
    angularVelocity += inverse_inertia * (contactVector.cross( impulse ));
  }

  void SetStatic( void )
  {
    inertia = 0.0f;
    inverse_inertia = 0.0f;
    mass = 0.0f;
    inverse_mass = 0.0f;
  }


  Vect2 velocity;

  float angularVelocity;
  float torque;

  Vect2 force;

  float inertia;  
  float inverse_inertia; 
  float mass;  
  float inverse_mass; 

  float static_friction;
  float dynamic_friction;
  float restitution;

  Shape *shape;

};


#endif