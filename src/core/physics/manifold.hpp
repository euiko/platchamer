#ifndef PHYSICS_MANIFOLD_HPP
#define PHYSICS_MANIFOLD_HPP

#include "rigid_body.hpp"

struct Manifold
{
  Manifold( RigidBody *a, RigidBody *b )
    : A( a )
    , B( b )
  {
  }

  void Solve( void );                 // Generate contact information
  void Initialize( void );            // Precalculations for impulse solving
  void ApplyImpulse( void );          // Solve impulse and apply
  void PositionalCorrection( void );  // Naive correction of positional penetration
  void InfiniteMassCorrection( void );

  RigidBody *A;
  RigidBody *B;

  float penetration;     // Depth of penetration from collision
  Vect2 normal;          // From A to B
  Vect2 contacts[2];     // Points of contact during collision
  uint32_t contact_count; // Number of contacts that occured during collision
  float e;               // Mixed restitution
  float df;              // Mixed dynamic friction
  float sf;              // Mixed static friction
};
#endif