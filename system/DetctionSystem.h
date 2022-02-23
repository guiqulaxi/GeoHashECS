#ifndef DETCTIONSYSTEM_H
#define DETCTIONSYSTEM_H

#include "EntityFu.h"

#include <Geohash.h>

class DetctionSystem: public System
{
public:
    DetctionSystem();
    //
    static void tick( float deltaTime) ;
    static void tick1( float deltaTime) ;
    static void tick2( float deltaTime) ;
    //use trietree
    static void tick3( float deltaTime) ;
    //use kdtree
    static void tick4(float deltaTime);
    //use rtree
    static void tick5(float deltaTime);

    static CGeoHash _geohash;

};

#endif // DETCTIONSYSTEM_H
