#ifndef ENTITY_H
#define ENTITY_H

#include <QtGlobal>
#include <QGraphicsItem>
#include <QPainter>


class Entity : public QGraphicsItem
{
public:
    Entity(qreal x, qreal y);

    void drawAt(qreal x, qreal y);

protected:
    qreal _x;
    qreal _y;
};

#endif // ENTITY_H
