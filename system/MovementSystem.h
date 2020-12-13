#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "EntityFu.h"

class MovementSystem: System
{
public:
    MovementSystem();
    static void tick( float deltaTime) ;
};

#endif // MOVEMENTSYSTEM_H
