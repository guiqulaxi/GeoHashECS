#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "EntityFu.h"
struct Movement:Entity::Component
{

    Movement() {}
    Movement(float direction, float speed):direction(direction),speed(speed){}
    Movement(float speedx, float speedy,float speedz):speedx(speedx),speedy(speedy),speedz(speedz){}
    float direction;
    float speed;
    float speedx;
    float speedy;
    float speedz;
    static Cid cid;
};


#endif // MOVEMENT_H
