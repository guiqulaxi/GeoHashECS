#ifndef SENSORDEVICE_H
#define SENSORDEVICE_H
#include <vector>
#include <string>
#include "EntityFu.h"
enum class SensorState :uint {
    On,
    Off,
    Broken
};
struct SensorDevice:Entity::Component
{


    SensorDevice() {}
    std::string name;
    std::vector<unsigned> target;
    SensorState  sensorState;

    static Cid cid;
};

#endif // SENSORDEVICE_H
