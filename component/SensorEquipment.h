#ifndef SENSOREQUIPMENT_H
#define SENSOREQUIPMENT_H
#include <vector>
#include <string>
#include <tuple>
#include "EntityFu.h"

struct SensorEquipment:Entity::Component
{


    SensorEquipment() {}
    std::vector<Eid> device;
    std::string name;
    std::vector<std::tuple<Entity::Component*,float>> otherPlatformDis2;
    static Cid cid;
};

#endif // SENSOREQUIPMENT_H
