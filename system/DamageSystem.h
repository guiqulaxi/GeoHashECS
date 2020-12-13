#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H
#include "ECS.h"
using namespace  ECS;
class DamageSystem:public EntitySystem
{
public:
    DamageSystem();
    virtual void tick(World* world, float deltaTime) override;
};

#endif // DAMAGESYSTEM_H
