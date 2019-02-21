#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "shapes/collider_shape.hpp"
#include "rigid_body.hpp"
#include "manifold.hpp"

typedef void (*CollisionCallback)( Manifold *m, RigidBody *a, RigidBody *b );

extern CollisionCallback Dispatch[ColliderShape::colliderCount][ColliderShape::colliderCount];

void CircletoCircle( Manifold *m, RigidBody *a, RigidBody *b );
void CircletoPolygon( Manifold *m, RigidBody *a, RigidBody *b );
void PolygontoCircle( Manifold *m, RigidBody *a, RigidBody *b );
void PolygontoPolygon( Manifold *m, RigidBody *a, RigidBody *b );

#endif