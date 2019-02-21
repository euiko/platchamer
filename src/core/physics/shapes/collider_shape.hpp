#ifndef COLLIDER_SHAPE_HPP
#define COLLIDER_SHAPE_HPP

#include "../../../types/matrix2.hpp"
#include "../rigid_body.hpp"

struct ColliderShape
{
  enum Type
  {
    colliderCircle,
    colliderPoly,
    colliderCount
  };

  ColliderShape( ) {}
  virtual ColliderShape *Clone( void ) const = 0;
  virtual RigidBody computeMass( float density ) = 0;
  virtual Type getType( void ) const = 0;

};

#endif