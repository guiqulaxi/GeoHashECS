#ifndef POSITION_H
#define POSITION_H

#include "EntityFu.h"
struct Position:Entity::Component
{


    Position(float x, float y,float z) : x(x), y(y),z(z) {}
    Position() {}

    float x;
    float y;
    float z;

    static Cid cid;
};


#endif // POSITION_H
