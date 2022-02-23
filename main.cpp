#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTime>
#include <QTimer>
#include "EntityFu.h"
#include "DisplayWidget.h"
#include "system/MovementSystem.h"
#include "system/DetctionSystem.h"
#include "system/CommunicationSystem.h"
#include "system/TrackSystem.h"
#include "system/FusionSystem.h"
#include "system/DisplaySystem.h"
#include "component/GCSPosition.h"
#include "component/Movement.h"
#include "component/Health.h"
#include "component/Platform.h"
#include "component/Detection.h"
#include "component/SensorEquipment.h"
#include "component/Fusion.h"
#include "component/SensorDevice.h"
#include "component/Ammo.h"
#include "component/Damage.h"
#include "component/Display.h"
#include "component/MovementFactor.h"
#include "component/CommunicationDevice.h"
#include "component/Guide.h"
#include "DisplayGraphicsItem.h"
#include <QDebug>
#include "GeoUtil.h"
#include "geodesic.h"
#include <component/CommunicationEquipment.h>
#include <component/WeaponDevice.h>
#include <component/WeaponEquipment.h>

Cid Detection::cid = Entity::Component::numCids++;
Cid Ammo::cid = Entity::Component::numCids++;
Cid CommunicationDevice::cid = Entity::Component::numCids++;
Cid Damage::cid = Entity::Component::numCids++;
Cid Display::cid = Entity::Component::numCids++;
Cid Fusion::cid = Entity::Component::numCids++;
Cid Guide::cid = Entity::Component::numCids++;
Cid Health::cid = Entity::Component::numCids++;
Cid Movement::cid = Entity::Component::numCids++;
Cid Platform::cid = Entity::Component::numCids++;
Cid GCSPosition::cid = Entity::Component::numCids++;
Cid SensorDevice::cid = Entity::Component::numCids++;
Cid WeaponDevice::cid = Entity::Component::numCids++;
Cid WeaponEquipment::cid = Entity::Component::numCids++;
Cid SensorEquipment::cid = Entity::Component::numCids++;
Cid CommunicationEquipment::cid = Entity::Component::numCids++;
Cid MovementFactor::cid = Entity::Component::numCids++;
#define NUM 50
double STEP=10000;
double RANGE=0;
double LNG_LAT[NUM][NUM][2];
void initLngLat()
{
    qsrand(time(nullptr));
    double lng,lat;
    Geo::polar(120,20,STEP/sqrt(2),45,lng,lat);
    double latStep=lat-20;
    double lngStep=lng-120;
    double  rate=qrand()/(1.0*RAND_MAX);
    for (int i=0;i<NUM;i++)
    {
        for(int j=0;j<NUM;j++)
        {
            LNG_LAT[i][j][0]=120+lngStep*i*rate;
            LNG_LAT[i][j][1]=20+latStep*j*rate;

        }
    }
}
void init()
{
    Entity::destroyAll();

    for (int i=0;i<NUM;i++)
    {
        for(int j=0;j<NUM;j++)
        {

            Eid eid=Entity::create( new GCSPosition(LNG_LAT[i][j][0],LNG_LAT[i][j][1],0),
                                    new Movement(90,1),
                                    new Platform,
                                    new Health,
                                    new MovementFactor);
          auto ss1= new SensorEquipment;

          Eid sd1=Entity::create(new SensorDevice("sd1"),new Detection(20));
          Eid sd2=Entity::create(new SensorDevice("sd2"),new Detection(RANGE));
          Eid sd3=Entity::create(new SensorDevice("sd3"),new Detection(100000));
          //ss1->device.push_back(sd1);
          ss1->device.push_back(sd2);
          //ss1->device.push_back(sd3);
          Entity::addComponent(eid,ss1);
        }
    }

}
void test()
{
    init();
    qWarning()<<"no";
    QTime time;
    time.start();


    for(int i=0;i<1;i++)
    {
        MovementSystem::tick(1);
        //DisplaySystem::tick(1);
        DetctionSystem::tick(1);
    }
    qWarning()<<time.elapsed()/1000.0<<"s";

}
void test1()
{
     qWarning()<<"test1";
   init();
    QTime time;
    time.start();

    for(int i=0;i<10;i++)
    {
        MovementSystem::tick(1);
        //DisplaySystem::tick(1);
        DetctionSystem::tick1(1);
    }
    qWarning()<<time.elapsed()/1000.0<<"s";
    Entity::destroyAll();
}
void test2()
{
qWarning()<<"test2";
     init();
    QTime time;
    time.start();

    for(int i=0;i<1;i++)
    {
        MovementSystem::tick(1);
        //DisplaySystem::tick(1);
        DetctionSystem::tick2(1);
    }
    qWarning()<<time.elapsed()/1000.0<<"s";

}
void test3()
{
qWarning()<<"ours";
     init();
    QTime time;
    time.start();

    for(int i=0;i<1;i++)
    {
        MovementSystem::tick(1);
        //DisplaySystem::tick(1);
        DetctionSystem::tick3(1);
    }
    qWarning()<<time.elapsed()/1000.0<<"s";

}
void test4()
{
qWarning()<<"kdtree";
     init();
    QTime time;
    time.start();

    for(int i=0;i<1;i++)
    {
        MovementSystem::tick(1);
        //DisplaySystem::tick(1);
        DetctionSystem::tick4(1);
    }
    qWarning()<<time.elapsed()/1000.0<<"s";

}
void test5()
{
qWarning()<<"rtree";
     init();
    QTime time;
    time.start();

    for(int i=0;i<1;i++)
    {
        MovementSystem::tick(1);
        //DisplaySystem::tick(1);
        DetctionSystem::tick5(1);
    }
    qWarning()<<time.elapsed()/1000.0<<"s";

}
#include<fstream>
void testall()
{
    std::ofstream ofile;
    ofile.open("result.txt", std::ios::out);//②
       if(!ofile)
       {

           exit(1);
       }


    std::vector<int> step={1000000};
     std::vector<int> ranges={50,100,500,1000,5000,10000,50000,100000,500000,1000000};

//       std::vector<int> step={100};
//        std::vector<int> ranges={50};
    ofile<<"Step"<<","<<"Range"<<","<<"no"<<","<<"ours(trietree-)"<<"ours(trietree+)"<<"ours(-geohash)"<<","<<"kdtree"<<","<<"rtree"<<std::endl;
    for(int i=0;i<step.size();i++)
    {
        STEP=step[i];
         initLngLat();
        for(int j=0;j<ranges.size();j++)
        {

             RANGE=ranges[j];
             if(STEP<=RANGE)
             {
                 continue;
             }
             init();
             DetctionSystem::tick(1);

             init();
             QTime time;
             time.start();
             DetctionSystem::tick(1);
             double t=time.elapsed()/1000.0;

             init();
             QTime time1;
             time1.start();
             DetctionSystem::tick1(1);
             double t1=time1.elapsed()/1000.0;

             init();
             QTime time2;
             time2.start();
             DetctionSystem::tick2(1);
             double t2=time2.elapsed()/1000.0;

             init();
             QTime time3;
             time3.start();
             DetctionSystem::tick3(1);
             double t3=time3.elapsed()/1000.0;

             init();
             QTime time4;
             time4.start();
             DetctionSystem::tick4(1);
             double t4=time4.elapsed()/1000.0;


             init();
             QTime time5;
             time5.start();
             DetctionSystem::tick5(1);
             double t5=time5.elapsed()/1000.0;

            //printf("[%f,%f]{%f,%f,%f,%f,%f,%f}\n",STEP,RANGE,t1,t2,1.0,2.0);
             printf("[%f,%f]{%f,%f,%f,%f,%f,%f}\n",STEP,RANGE,t,t1,t2,t3,t4,t5);
             ofile<<STEP<<","<<RANGE<<","<<t<<","<<t1<<","<<t2<<","<<t3<<","<<t4<<","<<t5<<std::endl;
        }
    }
      ofile.close();//④
}
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    double sis=Geo::distance(120.1,25,120,25);
    testall();
//    QGraphicsScene scene;

//    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
//    QGraphicsView view(&scene);
//    //    for(int i=0;i<100;i++)
//    //    {
//    //        QGraphicsEllipseItem *item=new QGraphicsEllipseItem(QRectF(0,0,10,10));
//    //       item->setPos(i*10,i*10);
//    //        scene.addItem(item);
//    //    }

//    view.setRenderHint(QPainter::Antialiasing);
//    //view.setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
//    view.setCacheMode(QGraphicsView::CacheBackground);
//    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
//    view.setDragMode(QGraphicsView::ScrollHandDrag);
//    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, ""));
//    view.setAlignment(Qt::AlignLeft | Qt::AlignTop);
//    view.resize(400, 300);
//    view.show();




   printf("50\n");
   //STEP=20;
   //RANGE=20;
   //initLngLat();
   //test();
//   test3();
//   test4();
   //test5();
//   printf("100\n");
//   range=100;
//   test();
//   test3();
//   test4();
//   test5();
//   printf("500\n");
//   range=500;
//   test();
//   test3();
//   test4();
//   test5();
  // printf("1000\n");
//   range=1000;
//   test();
//   test3();
//   test4();
//   test5();
   //printf("5000\n");
//   range=5000;
//   test();
//   test3();
//   test4();
//   test5();
   //printf("10000\n");
//   range=10000;
//   test();
//   test3();
//   test4();
//   test5();
//   printf("50000\n");
//   range=50000;
//   test();
//   test3();
//   test4();
//   test5();
//   printf("100000\n");
//   range=100000;
//   test();
//   test3();
//   test4();
//   test5();
//   printf("500000\n");
//   range=500000;
//   test();
//   test3();
//   test4();
//   test5();
   return a.exec();

}
