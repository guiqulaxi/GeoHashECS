#ifndef WEAPONEQUIPMENT_H
#define WEAPONEQUIPMENT_H
#include "EntityFu.h"
#include <vector>
#include <string>


struct WeaponEquipment:Entity::Component
{

    WeaponEquipment() {}
    std::vector<Entity::Component*> device;
    std::string name;
    static Cid cid;
};

#endif // WEAPONEQUIPMENT_H
