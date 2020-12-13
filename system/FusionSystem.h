#ifndef FUSIONSYSTEM_H
#define FUSIONSYSTEM_H

#include "EntityFu.h"



class FusionSystem:public System
{
public:
    FusionSystem();
    static void tick( float deltaTime) ;
};

#endif // FUSIONSYSTEM_H
