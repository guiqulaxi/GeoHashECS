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
<<<<<<< HEAD
    //use trietree
    static void tick3( float deltaTime) ;
    //use kdtree
    static void tick4(float deltaTime);
=======

>>>>>>> f247e8c1a555691977fadb705fe7f8b22cbfbb4e
private:
    static CGeoHash _geohash;

};

#endif // DETCTIONSYSTEM_H
