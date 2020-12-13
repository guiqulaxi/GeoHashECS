#ifndef COMMUNICATIONDEVICE_H
#define COMMUNICATIONDEVICE_H
#include <vector>
#include <string>
#include "EntityFu.h"

struct CommunicationDevice:Entity::Component
{

    CommunicationDevice() {}
    std::string name;
    std::vector<Eid> connectedDevice;
    std::vector<Eid> target;
    static Cid cid;
   };

#endif // COMMUNICATIONDEVICE_H
