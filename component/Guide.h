#ifndef GUIDE_H
#define GUIDE_H

#include <string>
#include "EntityFu.h"
struct Guide:Entity::Component
{

    Guide() {}
    unsigned ammoEid;
    unsigned targetEid;

    static Cid cid;
};

#endif // GUIDE_H
