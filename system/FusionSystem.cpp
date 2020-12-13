#include "FusionSystem.h"
#include  <set>
#include <QDebug>
#include "component/Fusion.h"
#include "component/SensorEquipment.h"
#include "component/SensorDevice.h"
#include "component/CommunicationEquipment.h"
#include "component/CommunicationDevice.h"
FusionSystem::FusionSystem()
{

}
void FusionSystem::tick( float deltaTime)
{

    auto all = Entity::getAll<Fusion>();
    for (auto eid : all)
    {


         auto fusion =Entity::getPointer<Fusion>(eid);
        auto sensorEquipment =Entity::getPointer<SensorEquipment>(eid);
        std::set<unsigned> alltarget;

         for(auto deid:sensorEquipment->device)
          {
                auto  sensorDevice=Entity::getPointer<SensorDevice>(deid);
                alltarget.insert(sensorDevice->target.begin(),sensorDevice->target.end());
          }



         auto communicationEquipment=Entity::getPointer<CommunicationEquipment>(eid);

           for(auto deid:communicationEquipment->device)
           {
                auto communicationDevice= Entity::getPointer<CommunicationDevice>(deid);
                alltarget.insert(communicationDevice->target.begin(),communicationDevice->target.end());
           }

           fusion->target.clear();
           fusion->target.assign(alltarget.begin(),alltarget.end());
           qDebug()<<fusion->target.size();
       }



}
