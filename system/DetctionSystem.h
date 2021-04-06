#ifndef DETCTIONSYSTEM_H
#define DETCTIONSYSTEM_H

#include "EntityFu.h"

class DetctionSystem: public System
{
public:
    DetctionSystem();
    static void tick( float deltaTime) ;
    static void tick1( float deltaTime) ;
    static void tick2( float deltaTime) ;
};

#endif // DETCTIONSYSTEM_H
