#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTime>
#include <QTimer>
#include "DisplayWidget.h"
#include "system/MovementSystem.h"
#include "system/DetctionSystem.h"
#include "system/CommunicationSystem.h"
#include "system/TrackSystem.h"
#include "system/FusionSystem.h"
#include "system/DisplaySystem.h"
#include "component/Position.h"
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
Cid Position::cid = Entity::Component::numCids++;
Cid SensorDevice::cid = Entity::Component::numCids++;
Cid WeaponDevice::cid = Entity::Component::numCids++;
Cid WeaponEquipment::cid = Entity::Component::numCids++;
Cid SensorEquipment::cid = Entity::Component::numCids++;
Cid CommunicationEquipment::cid = Entity::Component::numCids++;
Cid MovementFactor::cid = Entity::Component::numCids++;
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



    //world->registerSystem(new DamageSystem());
    //world->registerSystem(new CommunicationSystem());
   // world->registerSystem(new DetctionSystem());
   // world->registerSystem(new TrackSystem());
   // world->registerSystem(new FusionSystem());
    //world->registerSystem(new DisplaySystem(&scene));

    for (int i=0;i<1000;i++)
    {
       for(int j=0;j<100;j++)
       {
    Eid eid=Entity::create( new Position(i*10,0+j*20,0),
                            new Movement(45,1),
                            new Platform,
                            new Health,
                            new MovementFactor,
                            new Display);




//    Entity* sensor1 = world->create();
//    sensor1->assign<SensorDevice>();
//    sensor1->assign<Detection>(100);
//    sensor1->assign<Health>(100);
//    Entity* sensor2 = world->create();
//    sensor2->assign<SensorDevice>();
//    sensor2->assign<Detection>(50);
//    sensor2->assign<Health>(100);


    //auto sensorEquipmententA=entA->assign<SensorEquipment>();
    //sensorEquipmententA->device.push_back(sensor1);
    //sensorEquipmententA->device.push_back(sensor2);
    }
    }
//    for (int i=0;i<100;i++)
//    {
//       for(int j=0;j<100;j++)
//       {

//    Entity* entB = world->create();

//    entB->assign<Position>(300-i*10,300-j*20,0);
//    entB->assign<Movement>(225,1);
//    entB->assign<Health>(100);
//    entB->assign<Platform>();
//    entB->assign<Fusion>();
//    entB->assign<Display>();
//    entB->assign<MovementFactor>();

//    Entity* sensor3 = world->create();
//    sensor3->assign<SensorDevice>();
//    sensor3->assign<Detection>(100);
//    sensor3->assign<Health>(100);
//    Entity* sensor4 = world->create();
//    sensor4->assign<SensorDevice>();
//    sensor4->assign<Detection>(50);
//    sensor4->assign<Health>(100);

//    auto sensorEquipmententB=entB->assign<SensorEquipment>();
//    sensorEquipmententB->device.push_back(sensor3);
//    sensorEquipmententB->device.push_back(sensor4);
//       }}

//    Entity* torpedo = world->create();

//    torpedo->assign<Display>();
//    torpedo->assign<Position>(0,40,0);
//    torpedo->assign<Movement>(90,0);
//    torpedo->assign<Platform>();
//    torpedo->assign<Fusion>();
//    torpedo->assign<Ammo>();
//    torpedo->assign<Damage>();
//    torpedo->assign<MovementFactor>();

//    Entity* sensor5 = world->create();
//    sensor5->assign<SensorDevice>();
//    sensor5->assign<Detection>(50);
//    sensor5->assign<Health>(100);

//    auto sensorEquipmententT=torpedo->assign<SensorEquipment>();
//    sensorEquipmententT->device.push_back(sensor5);

DisplaySystem::m_pScene=&scene;


    QTimer timer;

    QObject::connect(&timer, &QTimer::timeout, [&](){
        QTime time;
        time.start();
        MovementSystem::tick(1);
        DisplaySystem::tick(1);
        qDebug()<<time.elapsed()/1000.0<<"s";

    });
    timer.start(1000/10 );

    return a.exec();

}
