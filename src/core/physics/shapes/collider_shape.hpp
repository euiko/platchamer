#ifndef COLLIDER_SHAPE_HPP
#define COLLIDER_SHAPE_HPP

#include "../../../types/matrix2.hpp"
// #include "../rigid_body.hpp"

struct RigidBody;

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
  virtual void initialize( void ) = 0;
  virtual void computeMass( float density ) = 0;
  virtual void setOrient( float radians ) = 0;
  virtual Type getType( void ) const = 0;


  RigidBody *body;
  // For circle shape
  float radius;
  // For Polygon shape
  Matrix2 u; // Orientation matrix from model to world

};

#endif