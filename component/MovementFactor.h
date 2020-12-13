#ifndef MOVEMENTFACTOR_H
#define MOVEMENTFACTOR_H
#include "EntityFu.h"
struct MovementFactor:Entity::Component
{

    MovementFactor() {}
    float maxSpeed=1;
    float maxAcceleration=1;
    float maxDeceleration=1;
    float maxTurnAngle=20;


    static Cid cid;
};

#endif // MOVEMENTFACTOR_H
