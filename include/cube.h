#ifndef CUBE_H
#define CUBE_H

#include "include/dynamicentity.h"


class Cube : public DynamicEntity
{
public:
    Cube(qreal x, qreal y, qreal size, QColor color = Qt::gray);

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Overrides from DynamicEntity
    void move();

private:
    qreal _size;
};

#endif // CUBE_H
