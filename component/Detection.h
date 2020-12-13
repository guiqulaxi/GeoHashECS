#ifndef DETECTION_H
#define DETECTION_H
#include "EntityFu.h"


struct Detection:Entity::Component
{

    Detection(float range) : range(range) {}
    Detection() {}

    float range;
    static Cid cid;
};

#endif // DETECTION_H
