#ifndef TYPES_COLLIDER_HPP
#define TYPES_COLLIDER_HPP

struct Collider
{
    enum Type
    {
        CircleCollider,
        PolygonCollider,
        ColliderCount
    };

    Type colliderType;
};

#endif