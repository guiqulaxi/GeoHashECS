#include "MovementSystem.h"
#include <math.h>
#include <tuple>
#include "component/Movement.h"
#include "component/Position.h"
#include "component/SensorEquipment.h"
#include "component/Platform.h"
MovementSystem::MovementSystem()
{

}
 void MovementSystem::tick( float deltaTime)
{
     auto all = Entity::getAll<Movement>();
     for (auto eid : all)
     {
        auto movement=Entity::getPointer<Movement>(eid);
        auto postion=Entity::getPointer<Position>(eid);
        float dis=movement->speed*deltaTime;
        postion->x+=dis*cosf(movement->direction/360*2*M_PI);
        postion->y+=dis*sinf(movement->direction/360*2*M_PI);
     }

}
