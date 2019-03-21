#ifndef TYPES_COLLIDER_HPP
#define TYPES_COLLIDER_HPP

#include "matrix2.hpp"

struct Collider
{
    enum Type
    {
        CircleCollider,
        PolygonCollider,
        ColliderCount
    };

    Type colliderType;

    Matrix2 orientation_matrix;
};

#endif