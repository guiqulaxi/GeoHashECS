#include "TrackSystem.h"
#include "component/Fusion.h"
#include "component/Position.h"
#include "component/MovementFactor.h"
#include "component/Movement.h"
#include "component/Ammo.h"
#include "Util.h"
#include <QDebug>
TrackSystem::TrackSystem()
{

}
void TrackSystem::tick(float deltaTime)
{
    auto all = Entity::getAll<Movement>();
    for (auto eid : all)
    {
        auto fusion=Entity::getPointer<Fusion>(eid);

        auto position=Entity::getPointer<Position>(eid);


        auto nearestEntity= std::min_element(fusion->target.begin(),fusion->target.end(),
                                                 [position](unsigned aeid, unsigned beid) -> bool{
                auto postionA=Entity::getPointer<Position>(aeid);
                auto postionB=Entity::getPointer<Position>(beid);
                return   std::pow(postionA->x-position->x,2)+std::pow(postionA->y-position->y,2)<
                std::pow(postionB->x-position->x,2)+std::pow(postionB->y-position->y,2);

         } );
        if(nearestEntity!=fusion->target.end())
        {
            auto nearestPos= Entity::getPointer<Position>(*nearestEntity);
            float targetAngle =std::atan2((nearestPos->y-position->y),(nearestPos->x-position->x));

            targetAngle=targetAngle/(2*M_PI)*360;
            targetAngle=limit(targetAngle,360);

            auto movementFactor=Entity::getPointer<MovementFactor>(eid);

            auto movement=Entity::getPointer<Movement>(eid);


            float deltaAngle=movementFactor->maxTurnAngle*deltaTime;

            float diff=diffAngle(movement->direction,targetAngle);

            if(std::abs(diff)<deltaAngle)
            {
               movement->direction=targetAngle;
            }
            else
            {
                if(diff<0)
                {
                   movement->direction=limit( movement->direction-deltaAngle,360);
                }else
                {
                    movement->direction=limit( movement->direction+deltaAngle,360);
                }
            }
            movement->speed=movement->speed+movementFactor->maxAcceleration*deltaTime;
            movement->speed=std::min(movement->speed,movementFactor->maxSpeed);
        }
    }


}
