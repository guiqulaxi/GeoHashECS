#include "CommunicationSystem.h"
#include "component/CommunicationDevice.h"
#include "component/CommunicationEquipment.h"
#include "component/Fusion.h"
#include"component/CommunicationDevice.h"
#include <set>
CommunicationSystem::CommunicationSystem()
{

}

void CommunicationSystem::tick( float deltaTime)
{

    auto all = Entity::getAll<CommunicationEquipment>();
    for(auto eid :all)
    {

      auto communicationEquipment=Entity::getPointer<CommunicationEquipment>(eid);

       //把设备的target放入 对应的连接设备的target
        for(auto deid: communicationEquipment->device)
        {
          auto communicationDevice=Entity::getPointer<CommunicationDevice>(deid);

          for(Eid dceid:communicationDevice->connectedDevice)
          {
               auto connectedDevice= Entity::getPointer<CommunicationDevice>(dceid);
               std::set<Eid> target;
               target.insert(connectedDevice->target.begin(),connectedDevice->target.end());
               target.insert(communicationDevice->target.begin(),communicationDevice->target.end());
               connectedDevice->target.clear();
               connectedDevice->target.assign(target.begin(),target.end());
          }

        }

    }
}
