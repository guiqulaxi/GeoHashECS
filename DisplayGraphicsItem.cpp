#include "DisplayGraphicsItem.h"

#include <QPainter>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include "component/Position.h"
#include "component/SensorEquipment.h"
#include "component/Detection.h"
#include "component/Movement.h"
DisplayGraphicsItem::DisplayGraphicsItem( Eid eid):m_eid(eid)
{
    setFlags(QGraphicsItem::ItemIsSelectable );
}
QRectF DisplayGraphicsItem::boundingRect() const
{
    auto position= Entity::getPointer<Position>(m_eid);

    QRectF rect= QRectF(position->x-5-m_penWidth/2,position->y-5-m_penWidth/2,20+m_penWidth*2,10+m_penWidth*2);
    if (isSelected())
    {
        auto sensorEquipment=Entity::getPointer<SensorEquipment>(m_eid);

        float maxRange=0;
        for(auto deid:sensorEquipment->device)
        {
            auto detection=Entity::getPointer<Detection>(deid);
            maxRange=qMax(detection->range,maxRange);
        }

        QRectF rectsensor= QRectF(position->x-maxRange-m_penWidth/2,
                                  -position->y-maxRange-m_penWidth/2,
                                  2*maxRange+m_penWidth*2,
                                  2*maxRange+m_penWidth*2);
        if(rectsensor.width()*rectsensor.height()<rect.width()*rect.height())
        {
            return rect;
        }
        else
        {
            return rectsensor;
        }


    }else
    {
        return QRectF(position->x-5-m_penWidth/2,-position->y-5-m_penWidth/2,20+m_penWidth*2,10+m_penWidth*2);
    }

}

void DisplayGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                QWidget *widget)
{

    m_sState=option->state;

    painter->save();
    auto position=Entity::getPointer<Position>(m_eid);


    QPainterPath path;
    //path.addRect(QRect(100,100,100,100));

    //path.addRect(QRect(m_fX-5,m_fY-5,20,10));
    path.moveTo(position->x-5,-position->y-5);
    path.lineTo(position->x+15,-position->y);
    path.lineTo(position->x-5,-position->y+5);
    path.lineTo(position->x-5,-position->y-5);
    if (option->state & QStyle::State_Selected)
    {
        painter->setPen(QPen(Qt::green, m_penWidth));

        auto sensorEquipment=Entity::getPointer<SensorEquipment>(m_eid);

        for(Eid deid:sensorEquipment->device)
        {
            auto detection=Entity::getPointer<Detection>(deid);
            path.addEllipse(QRectF(position->x-detection->range,-position->y-detection->range,2*detection->range,2*detection->range));
            path.addRect(QRectF(position->x-2*detection->range,-position->y-2*detection->range,4*detection->range,4*detection->range));
        }


    }
    else
    {
        painter->setPen(QPen(Qt::red,m_penWidth));

    }

    painter->drawPath(path);

    painter->restore();
}
void DisplayGraphicsItem::tick()
{

    auto position= Entity::getPointer<Position>(m_eid);


    setPos(position->x,-position->y);
    setTransformOriginPoint(position->x,-position->y);

    auto movement=Entity::getPointer<Movement>(m_eid);
    setRotation(-movement->direction);
}
