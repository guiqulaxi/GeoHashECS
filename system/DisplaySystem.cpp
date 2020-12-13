#include "DisplaySystem.h"
#include "component/Display.h"
#include "component/Position.h"
#include "component/Movement.h"
#include <QPainter>
#include <QDebug>
 QGraphicsScene *DisplaySystem::m_pScene=nullptr;
 QMap<unsigned,DisplayGraphicsItem*> DisplaySystem::m_mEntDisplayItem;
DisplaySystem::DisplaySystem()
{

}

void DisplaySystem::tick(  float deltaTime)
{
    auto all = Entity::getAll<Display>();
    for (auto eid : all)
    {

        auto position=Entity::getPointer<Position>(eid);

        auto movement=Entity::getPointer<Movement>(eid);

        if(!m_mEntDisplayItem.contains(eid))
        {
            DisplayGraphicsItem *item=new DisplayGraphicsItem(eid);

            m_mEntDisplayItem[eid]=item;
            m_pScene->addItem(item);
        }
        m_mEntDisplayItem[eid]->tick();

    }

}
