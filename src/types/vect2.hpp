#ifndef VECT2_HPP
#define VECT2_HPP

#include <math.h>

struct Vect2 {
    float x, y;

    Vect2(): x(0), y(0)
    {
    }

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

    Vect2 operator+ (float s) {
        return Vect2(this->x + s, this->y + s);
    }

    Vect2 operator- (float s) {
        return Vect2(this->x - s, this->y - s);
    }

    Vect2 operator+ (const Vect2& v) {
        return Vect2(this->x + v.x, this->y + v.y);
    }

    void operator+=( const Vect2& v )
    {
        x += v.x;
        y += v.y;
    }

    Vect2 operator- (const Vect2& v) {
        return Vect2(this->x - v.x, this->y - v.y);
    }

    void normalize() {
        float inv_len = 1 / length();
        x *= inv_len; y *= inv_len;
    }
    
    float dot(Vect2 a, Vect2 b) {
        return a.x * b.x + a.y * b.y;
    }
    
    // Two crossed vectors return a scalar pointing in the z direction
    float cross(const Vect2& b) {
        return x * b.y - y * b.x;
    }
    //A vector crossed with a scalar (z-axis) will return a vector on the 2D Cartesian plane
    Vect2 cross(float s) {
        return Vect2(s * y, -s * x);
    }
};

inline Vect2 operator*( float s, const Vect2& v )
{
  return Vect2( s * v.x, s * v.y );
};

inline Vect2 cross(float s, Vect2 a) 
{
    return Vect2(-s * a.y, s * a.x);
};

#endif