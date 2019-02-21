#include "rigid_body.hpp"
#include "shapes/collider_shape.hpp"

RigidBody::RigidBody( ColliderShape *shape_, uint32_t x, uint32_t y )
  : shape( shape_->Clone( ) )
{
  shape->body = this;
  position = {(float)x, (float)y};
  velocity = {0, 0};
  angular_velocity = 0;
  torque = 0;
  orient = generateRandom( -M_PI, M_PI );
  force = { 0, 0 };
  static_friction = 0.5f;
  dynamic_friction = 0.3f;
  restitution = 0.2f;
  shape->initialize( );
}

void RigidBody::SetOrient( float radians )
{
  orient = radians;
  shape->setOrient( radians );
}
