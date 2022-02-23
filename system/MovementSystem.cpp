#include "MovementSystem.h"
#include <math.h>
#include <tuple>
#include "component/Movement.h"
#include "component/GCSPosition.h"
#include "component/SensorEquipment.h"
#include "component/Platform.h"
#include "GeoUtil.h"
MovementSystem::MovementSystem()
{

}
 void MovementSystem::tick( float deltaTime)
{
     auto all = Entity::getAll<Movement>();
     for (auto eid : all)
     {
        auto movement=Entity::getPointer<Movement>(eid);
        auto postion=Entity::getPointer<GCSPosition>(eid);
        float dis=movement->speed*deltaTime;
        Geo::polar(postion->lon,postion->lat,dis,movement->direction,postion->lon,postion->lat);
     }

}
