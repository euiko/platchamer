#ifndef TYPES_MATRIX2_HPP
#define TYPES_MATRIX2_HPP

#include "vect2.hpp"

struct Matrix2
{
    enum RotationLock
    {
        NO_LOCK,
        LOCK_X,
        LOCK_Y,
        LOCK_ALL,
    } rotation_lock;

    float m[2][2];
    
    Matrix2( ) { }

    Matrix2(float m00, float m01, float m10, float m11) 
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[1][0] = m10;
        m[1][1] = m11;
    }
    //Create from angle in radians
    Matrix2(float radians) 
    {
        rotation_lock = RotationLock::NO_LOCK;
        float c = cos(radians);
        float s = sin(radians);

        m[0][0] = c; m[0][1] = -s;
        m[1][0] = s; m[1][1] =  c;
    }

    Matrix2(float radians, RotationLock rotation_lock ) :  rotation_lock(rotation_lock)
    {
        float rotationX = radians, rotationY = radians;
        if(rotation_lock == RotationLock::LOCK_Y || rotation_lock == RotationLock::LOCK_ALL)
        {
            rotationY = 0;
        }
        if(rotation_lock == RotationLock::LOCK_X || rotation_lock == RotationLock::LOCK_ALL)
        {
            rotationX = 0;
        }
        // float c = cos(radians);
        // float s = sin(radians);

        m[0][0] = cos(rotationX); m[0][1] = -sin(rotationY);
        m[1][0] = sin(rotationX); m[1][1] =  cos(rotationY);
    }
    
    Matrix2 transpose() {
        return Matrix2(m[0][0], m[1][0],
                       m[0][1], m[1][1]);
    }
    
    Vect2 operator*(Vect2 rhs) {
        return Vect2(m[0][0] * rhs.x + m[0][1] * rhs.y, m[1][0] * rhs.x + m[1][1] * rhs.y);
    }

    Matrix2 operator*(Matrix2 rhs ) {
    return Matrix2(
      m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0], m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
      m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0], m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]);
    }
};

#endif