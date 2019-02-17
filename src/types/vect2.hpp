#ifndef VECT2_HPP
#define VECT2_HPP

#include <math.h>

struct Vect2 {
    float x, y;

    Vect2(float x, float y) : x(x), y(y)
    {
    }

    float length() {
        return sqrt(x * x + y * y);
    }
    float sqrLength() {
        return x * x + y * y;
    }
    
    Vect2 operator* (float s) {
        return Vect2(this->x * s, this->y * s);
    }
    
    void normalize() {
        float inv_len = 1 / length();
        x *= inv_len; y *= inv_len;
    }
    
    float dot(Vect2 a, Vect2 b) {
        return a.x * b.x + a.y * b.y;
    }
    
    // Two crossed vectors return a scalar pointing in the z direction
    float cross(Vect2 a, Vect2 b) {
        return a.x * b.y - a.y * b.x;
    }
    //A vector crossed with a scalar (z-axis) will return a vector on the 2D Cartesian plane
    Vect2 cross(Vect2 a, float s) {
        return Vect2(s * a.y, -s * a.x);
    }
    Vect2 cross(float s, Vect2 a) {
        return Vect2(-s * a.y, s * a.x);
    }
};
#endif