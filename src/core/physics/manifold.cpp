#include <algorithm>
#include "manifold.hpp"
#include "collision.hpp"


const float gravityScale = 5.0f;
const Vect2 gravity( 0, 10.0f * gravityScale );
const float dt = 1.0f / 60.0f;

void Manifold::Solve( void )
{
    Dispatch[A->shape->getType( )][B->shape->getType( )]( this, A, B );
}

void Manifold::Initialize( void )
{
    // Calculate average restitution
    e = std::min( A->restitution, B->restitution );

    // Calculate static and dynamic friction
    sf = std::sqrt( A->static_friction * B->static_friction );
    df = std::sqrt( A->dynamic_friction * B->dynamic_friction );

    for(uint32_t i = 0; i < contact_count; ++i)
    {
        // Calculate radii from COM to contact
        Vect2 ra = contacts[i] - A->position;
        Vect2 rb = contacts[i] - B->position;

        Vect2 rv = B->velocity + cross( B->angular_velocity, rb ) -
                A->velocity - cross( A->angular_velocity, ra );


        // Determine if we should perform a resting collision or not
        // The idea is if the only thing moving this object is gravity,
        // then the collision should be performed without any restitution
        if(rv.sqrLength( ) < (dt * gravity).sqrLength( ) + EPSILON)
        e = 0.0f;
    }
}

void Manifold::ApplyImpulse( void )
{
    // Early out and positional correct if both objects have infinite mass
    if(equal( A->im + B->im, 0 ))
    {
        InfiniteMassCorrection( );
        return;
    }

    for(uint32_t i = 0; i < contact_count; ++i)
    {
        // Calculate radii from COM to contact
        Vect2 ra = contacts[i] - A->position;
        Vect2 rb = contacts[i] - B->position;

        // Relative velocity
        Vect2 rv = B->velocity + cross( B->angular_velocity, rb ) -
                A->velocity - cross( A->angular_velocity, ra );

        // Relative velocity along the normal
        float contactVel = rv.dot(normal);

        // Do not resolve if velocities are separating
        if(contactVel > 0)
            return;

        float raCrossN = cross( ra, normal );
        float rbCrossN = cross( rb, normal );
        float invMassSum = A->im + B->im + sqr( raCrossN ) * A->iI + sqr( rbCrossN ) * B->iI;

        // Calculate impulse scalar
        float j = -(1.0f + e) * contactVel;
        j /= invMassSum;
        j /= (float)contact_count;

        // Apply impulse
        Vect2 impulse = normal * j;
        A->ApplyImpulse( -impulse, ra );
        B->ApplyImpulse(  impulse, rb );

        // Friction impulse
        rv = B->velocity + cross( B->angular_velocity, rb ) -
            A->velocity - cross( A->angular_velocity, ra );

        Vect2 t = rv - (normal * rv.dot(normal));
        t.normalize( );

        // j tangent magnitude
        float jt = -rv.dot(t);
        jt /= invMassSum;
        jt /= (float)contact_count;

        // Don't apply tiny friction impulses
        if(equal( jt, 0.0f ))
            return;

        // Coulumb's law
        Vect2 tangentImpulse;
        if(std::abs( jt ) < j * sf)
            tangentImpulse = t * jt;
        else
            tangentImpulse = t * -j * df;

        // Apply friction impulse
        A->ApplyImpulse( -tangentImpulse, ra );
        B->ApplyImpulse(  tangentImpulse, rb );
    }
}

void Manifold::PositionalCorrection( void )
{
    const float k_slop = 0.05f; // Penetration allowance
    const float percent = 0.4f; // Penetration percentage to correct
    Vect2 correction = (std::max( penetration - k_slop, 0.0f ) / (A->im + B->im)) * normal * percent;
    A->position -= correction * A->im;
    B->position += correction * B->im;
}

void Manifold::InfiniteMassCorrection( void )
{
    A->velocity = { 0, 0 };
    B->velocity = { 0, 0 };
}
