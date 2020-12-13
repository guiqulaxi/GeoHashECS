#ifndef COMMUNICATIONEQUIPMENT_H
#define COMMUNICATIONEQUIPMENT_H
#include <vector>
#include <string>
#include "EntityFu.h"

struct CommunicationEquipment:Entity::Component
{

    CommunicationEquipment() {}
    std::vector<Eid> device;
    std::string name;
    static Cid cid;
};


#endif // COMMUNICATIONEQUIPMENT_H
