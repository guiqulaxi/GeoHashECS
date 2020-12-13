#include "DetctionSystem.h"
#include <math.h>
#include <map>
#include <set>
#include <QDebug>
#include <unordered_map>
#include "component/Detection.h"
#include "component/Position.h"
#include "component/Platform.h"
#include "component/SensorEquipment.h"
#include "component/SensorDevice.h"

DetctionSystem::DetctionSystem()
{

}



void DetctionSystem::tick( float deltaTime)
{


    //构建X轴排序，x轴差值 大于detection.range 肯定被排除
    std::vector<std::pair<Eid,float>> entOrderedX;
    std::unordered_map<Eid,int> entIndexX;
    //构建Y轴排序，Y轴差值 大于detection.range 肯定被排除
    std::vector<std::pair<Eid,float>> entOrderedY;
    std::unordered_map<Eid,int> entIndexY;
    //构建Z轴排序，Z轴差值 大于detection.range 肯定被排除
    std::vector<std::pair<Eid,float>> entOrderedZ;
    std::unordered_map<Eid,int> entIndexZ;
    auto all = Entity::getAll<Position>();
    for (auto eid : all)
    {
        auto position=Entity::getPointer<Position>(eid);
        entOrderedX.push_back(std::pair<Eid,float>(eid,position->x));
        entOrderedY.push_back(std::pair<Eid,float>(eid,position->y));
        entOrderedZ.push_back(std::pair<Eid,float>(eid,position->z));
    }

    auto cmp = [](std::pair<Eid,float> a, std::pair<Eid,float> b)->bool {
        return a.second<b.second; //如果是从小到大
    };
    std::sort(entOrderedX.begin(),entOrderedX.end(),cmp);
    std::sort(entOrderedY.begin(),entOrderedY.end(),cmp);
    std::sort(entOrderedZ.begin(),entOrderedZ.end(),cmp);
    for(size_t i=0;i<entOrderedX.size();i++)
    {
        entIndexX[entOrderedX[i].first]=i;
        entIndexY[entOrderedY[i].first]=i;
        entIndexZ[entOrderedZ[i].first]=i;
    }
     all = Entity::getAll<SensorEquipment>();
     for (auto eid : all)
     {

    auto sensorEquipment=Entity::getPointer<SensorEquipment>(eid);
        auto position=Entity::getPointer<SensorEquipment>(eid);
        auto position1=Entity::getPointer<Position>(eid);

        for(auto deid :sensorEquipment->device)
        {
            int indexX=entIndexX[eid];
            int indexY=entIndexY[eid];
            auto detection=Entity::getPointer<Detection>(deid);
            std::set<Eid> candinates;
            for(int i=indexX-1;i>=0;i--)
            {
                if(fabs(entOrderedX[i].second-position1->x)<=detection->range)
                {
                    candinates.insert(entOrderedX[i].first);
                }

            }
            for(size_t i=indexX+1;i<entOrderedX.size();i++)
            {
                if(fabs(entOrderedX[i].second-position1->x)<=detection->range)
                {
                    candinates.insert(entOrderedX[i].first);
                }
            }
            for(int i=indexY-1;i>=0;i--)
            {
                if(fabs(entOrderedY[i].second-position1->y)<=detection->range)
                {
                    candinates.insert(entOrderedY[i].first);
                }
            }
            for(size_t i=indexY+1;i<entOrderedY.size();i++)
            {
                if(fabs(entOrderedY[i].second-position1->y)<=detection->range)
                {
                    candinates.insert(entOrderedY[i].first);
                }
            }

            for(int i=indexY-1;i>=0;i--)
            {
                if(fabs(entOrderedY[i].second-position1->y)<=detection->range)
                {
                    candinates.insert(entOrderedY[i].first);
                }
            }
            for(size_t i=indexY+1;i<entOrderedY.size();i++)
            {
                if(fabs(entOrderedY[i].second-position1->y)<=detection->range)
                {
                    candinates.insert(entOrderedY[i].first);
                }
            }


            std::vector<Eid> target;

            for(auto eid:candinates)
            {
                auto position2=Entity::getPointer<Position>(eid);
                double  dis=std::pow(position1->x-position2->x,2)
                        +std::pow(position1->y-position2->y,2)
                        +std::pow(position1->z-position2->z,2);
                double range=detection->range;
                if(std::pow(position1->x-position2->x,2)
                        +std::pow(position1->y-position2->y,2)
                        +std::pow(position1->z-position2->z,2)
                        <=std::pow(detection->range,2))
                {
                    target.push_back(eid);
                }
            }




            auto sensorDevice =Entity::getPointer<SensorDevice>(deid);
            sensorDevice->target.clear();
            Entity::getPointer<SensorDevice>(deid)->target.assign(target.begin(),target.end());
        }
    }

}
