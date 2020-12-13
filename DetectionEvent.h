#ifndef DETECTIONEVENT_H
#define DETECTIONEVENT_H
#include "EntityFu.h"
struct DetectionEvent
{
    DetectionEvent( Entity * platform, Entity * sensor,Entity * target):platform(platform),sensor(sensor),target(target){}
    DetectionEvent():platform(nullptr),sensor(nullptr),target(nullptr){}
    Entity * platform;
    Entity * sensor;
    Entity * target;
};
#endif // DETECTIONEVENT_H
