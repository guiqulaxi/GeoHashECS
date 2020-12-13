#ifndef WEAPONDEVICE_H
#define WEAPONDEVICE_H

#include <vector>
#include <string>
#include "EntityFu.h"

struct WeaponDevice:Entity::Component
{

    WeaponDevice() {}

    std::string name;
    static Cid cid;
};

#endif // WEAPONDEVICE_H
