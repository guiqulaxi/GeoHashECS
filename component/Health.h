#ifndef HEALTH_H
#define HEALTH_H
#include "EntityFu.h"

struct Health:Entity::Component
{


    Health(float health) : health(health) {}
    Health() {}

    float health;

    static Cid cid;
};


#endif // HEALTH_H
