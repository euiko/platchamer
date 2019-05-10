#ifndef TYPES_VECT2_HPP
#define TYPES_VECT2_HPP

#include <math.h>
#include <rttr/type>

const float EPSILON = 0.0001f;

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

    Vect2 operator* (float s)
    {
        return Vect2(this->x * s, this->y * s);
    }

    void operator*=( float s )
    {
        x *= s;
        y *= s;
    }

    Vect2 operator/( float s ) const
    {
        return Vect2( x / s, y / s );
    }

    Vect2 operator+ (float s)
    {
        return Vect2(this->x + s, this->y + s);
    }

    Vect2 operator+ (const Vect2& v)
    {
        return Vect2(this->x + v.x, this->y + v.y);
    }

    void operator+=( const Vect2& v )
    {
        x += v.x;
        y += v.y;
    }

    Vect2 operator-( void ) const
    {
        return Vect2( -x, -y );
    }

    Vect2 operator-( const Vect2& v ) const
    {
        return Vect2( x - v.x, y - v.y );
    }

    Vect2 operator- (float s)
    {
        return Vect2(this->x - s, this->y - s);
    }

    Vect2 operator- (const Vect2& v)
    {
        return Vect2(this->x - v.x, this->y - v.y);
    }


    void operator-=( const Vect2& v )
    {
        x -= v.x;
        y -= v.y;
    }
    void normalize()
    {
        float len = length();
        if(len > EPSILON)
        {
            float inv_len = 1 / len;
            x *= inv_len; y *= inv_len;
        }

    }

    float dot(Vect2 b)
    {
        return x * b.x + y * b.y;
    }

    float cross(const Vect2& b)
    {
        return x * b.y - y * b.x;
    }

    Vect2 cross(float s)
    {
        return Vect2(s * y, -s * x);
    }

    template<class Archive>
    void serialize(Archive &ar)
    {
        ar(x,y);
    }

    RTTR_ENABLE();
};

inline Vect2 operator*( float s, const Vect2& v )
{
  return Vect2( s * v.x, s * v.y );
};

inline Vect2 cross(float s, Vect2 a)
{
    return Vect2(-s * a.y, s * a.x);
};

inline float cross(const Vect2& a, const Vect2& b)
{
    return a.x * b.y - a.y * b.x;
};


inline float dot(const Vect2& a, const Vect2& b)
{
    return a.x * b.x + a.y * b.y;
}

inline bool equal( float a, float b )
{
    return std::abs( a - b ) <= EPSILON;
}

inline float generateRandom(float l, float h)
{
    float a = (float)rand( );
    a /= RAND_MAX;
    a = (h - l) * a + l;
    return a;
}

inline float sqr( float a )
{
  return a * a;
}

inline float distSqr( const Vect2& a, const Vect2& b )
{
  Vect2 c = a - b;
  return c.dot( c );
}

inline bool biasGreaterThan( float a, float b )
{
  const float k_biasRelative = 0.95f;
  const float k_biasAbsolute = 0.01f;
  return a >= b * k_biasRelative + a * k_biasAbsolute;
}


#endif
