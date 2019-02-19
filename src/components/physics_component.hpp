#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP
#include <stdint.h>
#include "../types/shape.hpp"
#include "../types/vect2.hpp"

struct PhysicsComponent : Shape
{
  PhysicsComponent( Shape *shape_, uint32_t x, uint32_t y );

  void ApplyForce( const Vect2& f )
  {
    force += f;
  }

  void ApplyImpulse( const Vect2& impulse, const Vect2& contactVector )
  {
    velocity += im * impulse;
    angularVelocity += iI * contactVector.cross( impulse );
  }

  void SetStatic( void )
  {
    I = 0.0f;
    iI = 0.0f;
    m = 0.0f;
    im = 0.0f;
  }

  void SetOrient( float radians );

  Vect2 position;
  Vect2 velocity;

  float angularVelocity;
  float torque;
  float orient; // radians

  Vect2 force;

  // Set by shape
  float I;  // moment of inertia
  float iI; // inverse inertia
  float m;  // mass
  float im; // inverse masee

  // http://gamedev.tutsplus.com/tutorials/implementation/how-to-create-a-custom-2d-physics-engine-friction-scene-and-jump-table/
  float staticFriction;
  float dynamicFriction;
  float restitution;

  // Shape interface
  Shape *shape;

};


#endif