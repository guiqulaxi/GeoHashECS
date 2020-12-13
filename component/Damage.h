#ifndef DAMAGE_H
#define DAMAGE_H
#include <string>
#include "EntityFu.h"

struct Damage:Entity::Component
{

    Damage() {}
    float damage;
    float range;

    static Cid cid;
   };

#endif // DAMAGE_H
