#ifndef TYPES_MATRIX2_HPP
#define TYPES_MATRIX2_HPP

#include "vect2.hpp"

struct Matrix2
{
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
        float c = cos(radians);
        float s = sin(radians);

        m[0][0] = c; m[0][1] = -s;
        m[1][0] = s; m[1][1] =  c;
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