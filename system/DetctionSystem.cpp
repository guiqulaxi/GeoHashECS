#include "DetctionSystem.h"
#include <math.h>
#include <map>
#include <set>
#include <QDebug>
#include <unordered_map>
#include "component/Detection.h"
#include "component/GCSPosition.h"
#include "component/Platform.h"
#include "component/SensorEquipment.h"
#include "component/SensorDevice.h"
#include "Util.h"
#include "Geohash.h"
#include <vector>
#include <QHash>
#include <TireTree.h>
 CGeoHash DetctionSystem::_geohash;

DetctionSystem::DetctionSystem()
{

}

void cadinations1()
{

}
void DetctionSystem::tick( float deltaTime)
{
    qWarning()<<"tick";
    auto all = Entity::getAll<SensorEquipment>();
    std::vector<std::vector<double>> diss(all.size(),std::vector<double>(all.size(),-1));

    int i=0;
    for (auto eid : all)
    {

        auto sensorEquipment=Entity::getPointer<SensorEquipment>(eid);
        auto position1=Entity::getPointer<GCSPosition>(eid);

        for(auto deid :sensorEquipment->device)
        {

            auto detection=Entity::getPointer<Detection>(deid);
            std::vector<Eid> target;
            auto candinates = Entity::getAll<GCSPosition>();
            int j=0;
            for(auto eid1:candinates)
            {
                if(eid==eid1)
                    continue;
                auto position2=Entity::getPointer<GCSPosition>(eid1);
                double  dis=0;
                if(diss[i][j]<0)
                {
                       dis=  distance1(position1->lon,position1->lat,position2->lon,position2->lat);
                       diss[i][j]=dis;
                       diss[j][i]=dis;
                }else
                {
                      dis=diss[i][j];


    auto all = Entity::getAll<SensorEquipment>();
    //std:unordered_map<std::vector<double>> diss(all.size(),std::vector<double>(all.size(),-1));
    std::unordered_map<Eid,std::unordered_map<Eid,double>> diss;

    int count=0;
    for (auto eid : all)
    {

        auto sensorEquipment=Entity::getPointer<SensorEquipment>(eid);
        auto position1=Entity::getPointer<GCSPosition>(eid);

        for(auto deid :sensorEquipment->device)
        {

            auto detection=Entity::getPointer<Detection>(deid);
            std::vector<Eid> target;
            auto candinates = Entity::getAll<GCSPosition>();
            int j=0;
            for(auto eid1:candinates)
            {
                if(eid==eid1)
                    continue;
                auto position2=Entity::getPointer<GCSPosition>(eid1);
                double  dis=0;
                if(diss[eid][eid1]==0)
                {
                       dis=  distance1(position1->lon,position1->lat,position2->lon,position2->lat);
                       diss[eid][eid1]=dis;
                       diss[eid1][eid]=dis;

                }else
                {
                      dis=diss[eid1][eid];

                }

                double range=detection->range;

                if(dis<=range)
                {
                    target.push_back(eid1);
                    //qWarning()<<eid1;
                }
                j++;
            }
            count+=target.size();
            auto sensorDevice =Entity::getPointer<SensorDevice>(deid);
            sensorDevice->target.clear();
            Entity::getPointer<SensorDevice>(deid)->target.assign(target.begin(),target.end());

        }
    }

}
void DetctionSystem::tick1( float deltaTime)
{



    //??????Lon????????????x????????? ??????detection.range ???????????????
    std::vector<std::pair<Eid,float>> entOrderedLon;
    std::unordered_map<Eid,int> entIndexLon;
    //??????Lat????????????Lat????????? ??????detection.range ???????????????
    std::vector<std::pair<Eid,float>> entOrderedLat;
    std::unordered_map<Eid,int> entIndexLat;
    //??????Z????????????Z????????? ??????detection.range ???????????????
    std::vector<std::pair<Eid,float>> entOrderedZ;
    std::unordered_map<Eid,int> entIndexZ;
    auto all = Entity::getAll<GCSPosition>();
    for (auto eid : all)
    {
        auto position=Entity::getPointer<GCSPosition>(eid);
        entOrderedLon.push_back(std::pair<Eid,float>(eid,position->lon));
        entOrderedLat.push_back(std::pair<Eid,float>(eid,position->lat));
        entOrderedZ.push_back(std::pair<Eid,float>(eid,position->z));
    }

    auto cmp = [](std::pair<Eid,float> a, std::pair<Eid,float> b)->bool {
        return a.second<b.second; //????????????
    };
    std::sort(entOrderedLon.begin(),entOrderedLon.end(),cmp);
    std::sort(entOrderedLat.begin(),entOrderedLat.end(),cmp);
    std::sort(entOrderedZ.begin(),entOrderedZ.end(),cmp);
    for(size_t i=0;i<entOrderedLon.size();i++)
    {
        entIndexLon[entOrderedLon[i].first]=i;
        entIndexLat[entOrderedLat[i].first]=i;
        entIndexZ[entOrderedZ[i].first]=i;
    }
    all = Entity::getAll<SensorEquipment>();
    int count=0;

    for (auto eid : all)
    {

        auto sensorEquipment=Entity::getPointer<SensorEquipment>(eid);
        auto position1=Entity::getPointer<GCSPosition>(eid);

        for(auto deid :sensorEquipment->device)
        {
            int indexLon=entIndexLon[eid];
            int indexLat=entIndexLat[eid];
            auto detection=Entity::getPointer<Detection>(deid);
            std::set<Eid> candinates;
            for(int i=indexLon-1;i>=0;i--)
            {
                if(fabs(entOrderedLon[i].second-position1->lon)*EARTH_ARC * cos(rad(position1->lat))<=detection->range)
                {
                    candinates.insert(entOrderedLon[i].first);
                }

            }
            for(size_t i=indexLon+1;i<entOrderedLon.size();i++)
            {
                if(fabs(entOrderedLon[i].second-position1->lon)*EARTH_ARC * cos(rad(position1->lat))<=detection->range)
                {
                    candinates.insert(entOrderedLon[i].first);
                }
            }


            for(int i=indexLat-1;i>=0;i--)
            {
                if(rad(fabs(entOrderedLat[i].second-position1->lat))*EARTH_ARC<=detection->range)
                {
                    candinates.insert(entOrderedLat[i].first);
                }
            }
            for(size_t i=indexLat+1;i<entOrderedLat.size();i++)
            {
                if(rad(fabs(entOrderedLat[i].second-position1->lat))*EARTH_ARC<=detection->range)
                {
                    candinates.insert(entOrderedLat[i].first);
                }
            }


            std::vector<Eid> target;

            for(auto eid1:candinates)
            {
                auto position2=Entity::getPointer<GCSPosition>(eid1);
                double  dis=  distance1(position1->lon,position1->lat,position2->lon,position2->lat);
                double range=detection->range;
                if(dis<=range)
                {
                    target.push_back(eid1);



                }
            }
           count+=target.size() ;
            auto sensorDevice =Entity::getPointer<SensorDevice>(deid);
            sensorDevice->target.clear();
            Entity::getPointer<SensorDevice>(deid)->target.assign(target.begin(),target.end());
            //qWarning()<<Entity::getPointer<SensorDevice>(deid)->target.size();
        }
    }



}


struct S
{
    Eid id;
    int orderIndex;
    int geohashIndex;
    std::string geohash;

};

//void DetctionSystem::tick2( float deltaTime)
//{
//    std::string str;

//    auto all = Entity::getAll<GCSPosition>();
//    //??????????????????Geohash
//    std::vector<S> geohashcodes;
//    int i=0;
//    for (auto eid : all)
//    {
//        auto position=Entity::getPointer<GCSPosition>(eid);

//        str=_geohash.Encode(position->lat,position->lon,9);

//        S s;
//        s.id=eid;
//        s.orderIndex=i;
//        s.geohash=str;
//        geohashcodes.push_back(s);
//        i++;

//    }

//    auto cmp = [](const S& a, const S& b)->bool {
//        return a.geohash<b.geohash; //????????????
//    };

//    std::sort(geohashcodes.begin(),geohashcodes.end(),cmp);
//    QHash<Eid,S> Eid_S;

//    std::unordered_map<int ,std::unordered_map<std::string,std::vector<S>>> effectnum_geohash_Ss;
//    for(size_t i=0;i<geohashcodes.size();i++)
//    {
//           geohashcodes[i].geohashIndex=i;
//           Eid_S[geohashcodes[i].id]=geohashcodes[i];
//          for(size_t j=1;j<=8;j++)
//          {
//             std::string effectStr=geohashcodes[i].geohash.substr(0,j);
//             effectnum_geohash_Ss[j][effectStr].push_back(geohashcodes[i]);
//          }
//    }


//    //std::vector<std::vector<double>> diss(all.size(),std::vector<double>(all.size(),-1));

//    all = Entity::getAll<SensorEquipment>();
//    int count=0;
//    for (auto eid : all)
//    {

//        auto sensorEquipment=Entity::getPointer<SensorEquipment>(eid);
//        auto position1=Entity::getPointer<GCSPosition>(eid);

//        for(auto deid :sensorEquipment->device)
//        {

//            auto detection=Entity::getPointer<Detection>(deid);

//            S s=Eid_S[eid];
//            //?????????Geohash???????????????
//            int effectnum=_geohash.GetDistancePrecision(detection->range);
//            std::string effectStr=s.geohash.substr(0,effectnum);
//            std::vector<S> candinates;
//            candinates=effectnum_geohash_Ss[effectnum][effectStr];

//            std::vector<Eid> target;

//            for(auto cs:candinates)
//            {

//                double  dis=0;
//                auto position2=Entity::getPointer<GCSPosition>(cs.id);
//                dis=  distance1(position1->lon,position1->lat,position2->lon,position2->lat);
//                double range=detection->range;
//                if(dis<=range)
//                {

//                    target.push_back(cs.id);
//                }
//            }
//            count+=target.size();
//            auto sensorDevice =Entity::getPointer<SensorDevice>(deid);
//            sensorDevice->target.clear();
//            Entity::getPointer<SensorDevice>(deid)->target.assign(target.begin(),target.end());
//            //qWarning()<<Entity::getPointer<SensorDevice>(deid)->target.size();
//        }
//    }
//    qWarning()<<count;

//}
void DetctionSystem::tick2( float deltaTime)
{
    std::string str;

    auto all = Entity::getAll<GCSPosition>();
    //??????????????????Geohash
    std::unordered_map<Eid,std::string> id_geohash;
    int i=0;
    TireTree<Eid> tireTree;
    for (auto eid : all)
    {
        auto position=Entity::getPointer<GCSPosition>(eid);

        str=_geohash.Encode(position->lat,position->lon,9);

        tireTree.add(str,eid);
        i++;
        id_geohash[eid]=str;

    }




    //std::vector<std::vector<double>> diss(all.size(),std::vector<double>(all.size(),-1));

    all = Entity::getAll<SensorEquipment>();

    int count=0;


    for (auto eid : all)
    {

        auto sensorEquipment=Entity::getPointer<SensorEquipment>(eid);
        auto position1=Entity::getPointer<GCSPosition>(eid);

        for(auto deid :sensorEquipment->device)
        {

            auto detection=Entity::getPointer<Detection>(deid);


            //?????????Geohash???????????????
            int effectnum=_geohash.GetDistancePrecision(detection->range);
            std::string effectStr=id_geohash[eid].substr(0,effectnum);
             std::vector<Eid> candinates;
            tireTree.get(effectStr,candinates,false);
            //qWarning()<<candinates.size();

            std::vector<Eid> target;

            for(auto id:candinates)
            {
                if(id==eid)
                    continue;
                double  dis=0;
                auto position2=Entity::getPointer<GCSPosition>(id);

                dis=  distance1(position1->lon,position1->lat,position2->lon,position2->lat);
                double range=detection->range;
                if(dis<=range)
                {


                    target.push_back(id);

                }

            }
            count+=target.size();


            auto sensorDevice =Entity::getPointer<SensorDevice>(deid);
            sensorDevice->target.clear();
            Entity::getPointer<SensorDevice>(deid)->target.assign(target.begin(),target.end());
            //qWarning()<<Entity::getPointer<SensorDevice>(deid)->target.size();
        }
    }


}



