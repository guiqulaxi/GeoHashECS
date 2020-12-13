#ifndef DISPLAYSYSTEM_H
#define DISPLAYSYSTEM_H

#include <QGraphicsScene>
#include "DisplayGraphicsItem.h"
#include "EntityFu.h"


class DisplaySystem:public System
{
public:
    DisplaySystem();
    DisplaySystem(QGraphicsScene * scene);
    static void tick(float deltaTime) ;

    static QGraphicsScene *m_pScene;
    static QMap<Eid,DisplayGraphicsItem*> m_mEntDisplayItem;
};


#endif // DISPLAYSYSTEM_H
