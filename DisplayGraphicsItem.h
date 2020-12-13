#ifndef DISPLAYGRPHICSITEM_H
#define DISPLAYGRPHICSITEM_H

#include <QGraphicsItem>
#include<QStyle>
#include "EntityFu.h"
class DisplayGraphicsItem : public QGraphicsItem
{
public:
    DisplayGraphicsItem( Eid eid);
    void tick();
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) override;
private:


    qreal m_penWidth=2;
    QStyle::State m_sState;
    Eid m_eid;

};

#endif // DISPLAYGRPHICSITEM_H
