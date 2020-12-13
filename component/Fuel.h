#ifndef FUEL_H
#define FUEL_H
#include "EntityFu.h"
#include <string>


struct Fuel:Entity::Component
{

    Fuel() {}
    float volume; 
    static Cid cid;
};
Cid Fuel::cid = Entity::Component::numCids++;

#endif // FUEL_H
