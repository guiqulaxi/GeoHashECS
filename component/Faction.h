#ifndef FACTION_H
#define FACTION_H
#include "EntityFu.h"
#include <string>

enum class EFaction :uint {
    Red,
    Blue,
    Neutral
};
struct Faction:Entity::Component
{

    Faction() {}
    EFaction  faction;
    static Cid cid;
};
Cid Faction::cid = Entity::Component::numCids++;

#endif // FACTION_H
