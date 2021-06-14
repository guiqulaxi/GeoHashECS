#ifndef MOVEMENTFACTOR_H
#define MOVEMENTFACTOR_H
#include "EntityFu.h"
struct MovementFactor:Entity::Component
{

    MovementFactor() {}
    float maxSpeed=1; //m/s
    float maxAcceleration=1; //m/s2
    float maxDeceleration=1;//m/s2
    float maxTurnAngle=20; // dgree/s


    static Cid cid;
};

#endif // MOVEMENTFACTOR_H
