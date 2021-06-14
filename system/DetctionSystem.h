#ifndef DETCTIONSYSTEM_H
#define DETCTIONSYSTEM_H

#include "EntityFu.h"

#include <Geohash.h>

class DetctionSystem: public System
{
public:
    DetctionSystem();
    static void tick( float deltaTime) ;
    static void tick1( float deltaTime) ;
    static void tick2( float deltaTime) ;
private:
    static CGeoHash _geohash;
};

#endif // DETCTIONSYSTEM_H
