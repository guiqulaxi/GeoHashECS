#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include "EntityFu.h"
//所有有形实体都是platform
struct Platform:Entity::Component
{


    Platform() {}
    std::string name;
    std::string model;
    //size
    static Cid cid;
};


#endif // PLATFORM_H
