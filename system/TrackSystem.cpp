#include "TrackSystem.h"
#include "component/Fusion.h"
#include "component/GCSPosition.h"
#include "component/MovementFactor.h"
#include "component/Movement.h"
#include "component/Ammo.h"
#include "GeoUtil.h"
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

        auto position=Entity::getPointer<GCSPosition>(eid);


        auto nearestEntity= std::min_element(fusion->target.begin(),fusion->target.end(),
                                                 [position](unsigned aeid, unsigned beid) -> bool{
                auto positionA=Entity::getPointer<GCSPosition>(aeid);
                auto positionB=Entity::getPointer<GCSPosition>(beid);
                return  distance1(positionA->lon,positionA->lat,position->lon,position->lat)<
                distance1(positionB->lon,positionB->lat,position->lon,position->lat);

         } );
        if(nearestEntity!=fusion->target.end())
        {
            auto nearestPos= Entity::getPointer<GCSPosition>(*nearestEntity);
            float targetAngle =azimuth(nearestPos->lon,nearestPos->lat,nearestPos->lon,nearestPos->lat);

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
