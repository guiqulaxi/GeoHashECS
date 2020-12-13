#ifndef TRACKSYSTEM_H
#define TRACKSYSTEM_H
#include "EntityFu.h"

class TrackSystem:public System
{
public:
    TrackSystem();
    static void tick( float deltaTime);
};

#endif // TRACKSYSTEM_H
