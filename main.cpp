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
#include "Util.h"
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
void init()
{
    Entity::destroyAll();

    for (int i=0;i<50;i++)
    {
        for(int j=0;j<50;j++)
        {
            Eid eid=Entity::create( new GCSPosition(120+0.7*i,25+j*0.7,0),
                                    new Movement(90,1),
                                    new Platform,
                                    new Health,
                                    new MovementFactor);
          auto ss1= new SensorEquipment;

          Eid sd1=Entity::create(new SensorDevice("sd1"),new Detection(20));
          Eid sd2=Entity::create(new SensorDevice("sd2"),new Detection(10000));
          Eid sd3=Entity::create(new SensorDevice("sd3"),new Detection(100000));
          ss1->device.push_back(sd1);
          //ss1->device.push_back(sd2);
          //ss1->device.push_back(sd3);
          Entity::addComponent(eid,ss1);
        }
    }

}
void test()
{
    init();
    QTime time;
    time.start();

    for(int i=0;i<10;i++)
    {
        MovementSystem::tick(1);
        //DisplaySystem::tick(1);
        DetctionSystem::tick(1);
    }
    qWarning()<<time.elapsed()/1000.0<<"s";
    Entity::destroyAll();
}
void test1()
{
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

     init();
    QTime time;
    time.start();

    for(int i=0;i<10;i++)
    {
        MovementSystem::tick(1);
        //DisplaySystem::tick(1);
        DetctionSystem::tick2(1);
    }
    qWarning()<<time.elapsed()/1000.0<<"s";
    Entity::destroyAll();
}

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    QGraphicsScene scene;

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    QGraphicsView view(&scene);
    //    for(int i=0;i<100;i++)
    //    {
    //        QGraphicsEllipseItem *item=new QGraphicsEllipseItem(QRectF(0,0,10,10));
    //       item->setPos(i*10,i*10);
    //        scene.addItem(item);
    //    }

    view.setRenderHint(QPainter::Antialiasing);
    //view.setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, ""));
    view.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view.resize(400, 300);
    view.show();



   test();
   //test1();
   test2();
   return a.exec();

}
