#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP

struct RigidBody
{
    float inertia;
    float inverse_inertia;
    float mass;
    float inverse_mass;
};

#endif