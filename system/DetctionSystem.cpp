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
#include "GeoUtil.h"
#include "Geohash.h"
#include <vector>
#include <QHash>
#include "trietree/TireTree.h"
#include "kdtree/Point.hpp"
#include "kdtree/KDTreeUtil.hpp"
#include "kdtree/KDTree.hpp"
#include "rtree/RTree.h"
CGeoHash DetctionSystem::_geohash;
DetctionSystem::DetctionSystem()
{

}

void cadinations1()
{

}
void DetctionSystem::tick( float deltaTime)
{

    auto all = Entity::getAll<SensorEquipment>();
    //std::vector<std::vector<double>> diss(all.size(),std::vector<double>(all.size(),-1));
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
                    dis=   Geo::distance(position1->lon,position1->lat,position2->lon,position2->lat);
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
                    //qWarning()<<eid<<"-->"<<eid1;
                }
                j++;
            }
            count+=target.size();
            auto sensorDevice =Entity::getPointer<SensorDevice>(deid);
            //sensorDevice->target.clear();
            //Entity::getPointer<SensorDevice>(deid)->target.assign(target.begin(),target.end());

        }
    }

}
void DetctionSystem::tick1( float deltaTime)
{

    std::string str;

    auto all = Entity::getAll<GCSPosition>();
    //所有位置转为Geohash
    std::unordered_map<Eid,std::string> id_geohash;

    TrieTree<Eid> trieTree;

    for (auto eid : all)
    {
        auto position=Entity::getPointer<GCSPosition>(eid);
        str=_geohash.Encode(position->lat,position->lon,9);
        //str=position->geohash;

        id_geohash[eid]=str;
        trieTree.insert(str,eid);
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


            //要使用Geohash的误差位数
            int effectnum=_geohash.GetDistancePrecision(detection->range);
            std::string effectStr=id_geohash[eid].substr(0,effectnum);
            std::unordered_map<std::string,Eid> candinates;
            //获得当前区域
            trieTree.prefix(effectStr,candinates);
            //获得相邻八个
            std::vector<std::string> rs;
            _geohash.GetNeighbors(effectStr,rs);
            for(auto ss:rs)
            {
                std::unordered_map<std::string,Eid> cds;
                trieTree.prefixnormal(ss,cds);
                candinates.insert(cds.begin(),cds.end());
            }


            std::vector<Eid> target;

            for(auto hash_id:candinates)
            {
                std::string geohash=hash_id.first;
                Eid id=hash_id.second;
                if(id==eid)
                    continue;
                double  dis=0;
                auto position2=Entity::getPointer<GCSPosition>(id);

                dis=   Geo::distance(position1->lon,position1->lat,position2->lon,position2->lat);
                double range=detection->range;
                if(dis<=range)
                {


                    target.push_back(id);
                    //qWarning()<<eid<<"-->"<<id;
                }

            }
            count+=target.size();


            auto sensorDevice =Entity::getPointer<SensorDevice>(deid);
            //sensorDevice->target.clear();
            //Entity::getPointer<SensorDevice>(deid)->target.assign(target.begin(),target.end());
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

void DetctionSystem::tick2( float deltaTime)
{
    std::string str;

    auto all = Entity::getAll<GCSPosition>();
    //所有位置转为Geohash
    std::unordered_map<Eid,std::string> id_geohash;

    TrieTree<Eid> trieTree;

    for (auto eid : all)
    {
        auto position=Entity::getPointer<GCSPosition>(eid);
        str=_geohash.Encode(position->lat,position->lon,9);
        //str=position->geohash;

        id_geohash[eid]=str;
        trieTree.insert(str,eid);
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


            //要使用Geohash的误差位数
            int effectnum=_geohash.GetDistancePrecision(detection->range);
            std::string effectStr=id_geohash[eid].substr(0,effectnum);
            std::unordered_map<std::string,Eid> candinates;
            //获得当前区域
            trieTree.prefix(effectStr,candinates);
            //获得相邻八个
            std::vector<std::string> rs;
            _geohash.GetNeighbors(effectStr,rs);
            for(auto ss:rs)
            {
                std::unordered_map<std::string,Eid> cds;
                trieTree.prefix(ss,cds);
                candinates.insert(cds.begin(),cds.end());
            }


            std::vector<Eid> target;

            for(auto hash_id:candinates)
            {
                std::string geohash=hash_id.first;
                Eid id=hash_id.second;
                if(id==eid)
                    continue;
                double  dis=0;
                auto position2=Entity::getPointer<GCSPosition>(id);

                dis=   Geo::distance(position1->lon,position1->lat,position2->lon,position2->lat);
                double range=detection->range;
                if(dis<=range)
                {


                    target.push_back(id);
                    //qWarning()<<eid<<"-->"<<id;
                }

            }
            count+=target.size();


            auto sensorDevice =Entity::getPointer<SensorDevice>(deid);
            //sensorDevice->target.clear();
            //Entity::getPointer<SensorDevice>(deid)->target.assign(target.begin(),target.end());
            //qWarning()<<Entity::getPointer<SensorDevice>(deid)->target.size();
        }
    }

}



void DetctionSystem::tick3( float deltaTime)
{
    std::string str;

    auto all = Entity::getAll<GCSPosition>();
    //所有位置转为Geohash
    std::unordered_map<Eid,std::string> id_geohash;

    TrieTree<Eid> trieTree;

    for (auto eid : all)
    {
        auto position=Entity::getPointer<GCSPosition>(eid);
        //str=_geohash.Encode(position->lat,position->lon,9);
        str=position->geohash;

        id_geohash[eid]=str;
        trieTree.insert(str,eid);
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


            //要使用Geohash的误差位数
            int effectnum=_geohash.GetDistancePrecision(detection->range);
            std::string effectStr=id_geohash[eid].substr(0,effectnum);
            std::unordered_map<std::string,Eid> candinates;
            //获得当前区域
            trieTree.prefix(effectStr,candinates);
            //获得相邻八个
            std::vector<std::string> rs;
            _geohash.GetNeighbors(effectStr,rs);
            for(auto ss:rs)
            {
                std::unordered_map<std::string,Eid> cds;
                trieTree.prefix(ss,cds);
                candinates.insert(cds.begin(),cds.end());
            }


            std::vector<Eid> target;

            for(auto hash_id:candinates)
            {
                std::string geohash=hash_id.first;
                Eid id=hash_id.second;
                if(id==eid)
                    continue;
                double  dis=0;
                auto position2=Entity::getPointer<GCSPosition>(id);

                dis=   Geo::distance(position1->lon,position1->lat,position2->lon,position2->lat);
                double range=detection->range;
                if(dis<=range)
                {


                    target.push_back(id);
                    //qWarning()<<eid<<"-->"<<id;
                }

            }
            count+=target.size();


            auto sensorDevice =Entity::getPointer<SensorDevice>(deid);
            //sensorDevice->target.clear();
            //Entity::getPointer<SensorDevice>(deid)->target.assign(target.begin(),target.end());
            //qWarning()<<Entity::getPointer<SensorDevice>(deid)->target.size();
        }
    }


}

void DetctionSystem::tick4(float deltaTime)
{
    //_kdtree->radiusSearch(ns_geo::Point2d(120.0,20.0), 10460, vec, dis);

    ns_geo::PointSet2<Eid> ps;
    auto all = Entity::getAll<GCSPosition>();
    for (auto eid : all)
    {
        auto position=Entity::getPointer<GCSPosition>(eid);
        ps.push_back(ns_geo::Point2<Eid>(position->lon, position->lat));

    }
    ns_geo::KdTree2<ns_geo::Point2<Eid>> _kdtree(ps);



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
            std::vector<ns_geo::Point2<Eid>> vec;
            std::vector<float> dis;
            _kdtree.radiusSearch(ns_geo::Point2<Eid>(position1->lon,position1->lat), detection->range, vec, dis);

            std::vector<Eid> target;
            auto sensorDevice =Entity::getPointer<SensorDevice>(deid);
            //sensorDevice->target.clear();

            for(auto point:vec)
            {
                Entity::getPointer<SensorDevice>(deid)->target.push_back(point.value());
            }
            count+=target.size();
            //qWarning()<<Entity::getPointer<SensorDevice>(deid)->target.size();
        }
    }
}
bool search_iter(const double *rect, const void *item, void *udata) {
    const Eid *pid = (const Eid*)item;
    ((std::vector<Eid>*)udata)->push_back(*pid);
    return true;
}
void DetctionSystem::tick5(float deltaTime)
{
    //_kdtree->radiusSearch(ns_geo::Point2d(120.0,20.0), 10460, vec, dis);

    struct rtree *tr = rtree_new(sizeof(Eid*), 2);
    auto all = Entity::getAll<GCSPosition>();
    for (auto eid : all)
    {
        auto position=Entity::getPointer<GCSPosition>(eid);
        Eid *pid=(Eid*)malloc(sizeof (Eid));

        *pid=eid;
        double *pos=new double[4]{position->lon,position->lat,position->lon,position->lat };
        rtree_insert(tr, pos, pid);

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
            std::vector<ns_geo::Point2<Eid>> vec;
            std::vector<float> dis;
            GeoRect rect=_geohash.GetBoundingBox(position1->lat,position1->lon,detection->range);
            double rect1[4]={rect.west, rect.south,rect.east, rect.north };
            std::vector<Eid> candinates;
            rtree_search(tr,rect1, search_iter, &candinates);
            std::vector<Eid> target;


            for(auto id:candinates)
            {


                if(id==eid)
                    continue;
                double  dis=0;
                auto position2=Entity::getPointer<GCSPosition>(id);

                dis=   Geo::distance(position1->lon,position1->lat,position2->lon,position2->lat);
                double range=detection->range;
                if(dis<=range)
                {


                    target.push_back(id);
                    //qWarning()<<eid<<"-->"<<id;
                }
            }


            Entity::getPointer<SensorDevice>(deid)->target=target;
            count+=target.size();



            //qWarning()<<Entity::getPointer<SensorDevice>(deid)->target.size();
        }
    }
}
