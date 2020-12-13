#ifndef FUSION_H
#define FUSION_H
#include "EntityFu.h"

struct Fusion:Entity::Component
{


    Fusion() {}
    std::vector<Eid> target;

    static Cid cid;
};

#endif // FUSION_H
