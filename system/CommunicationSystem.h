#ifndef COMMUNICATIONSYSTEM_H
#define COMMUNICATIONSYSTEM_H
#include "EntityFu.h"



class CommunicationSystem :System
{
public:
    CommunicationSystem();
    virtual void tick( float deltaTime) ;
};

#endif // COMMUNICATIONSYSTEM_H
