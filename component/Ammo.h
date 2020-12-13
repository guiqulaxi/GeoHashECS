#ifndef AMMO_H
#define AMMO_H
#include <string>
#include "EntityFu.h"


struct Ammo:Entity::Component
{


    Ammo() {}
    std::vector<Eid> hitTarget;
    static Cid cid;
};

#endif // AMMOCOMPONENT_H
