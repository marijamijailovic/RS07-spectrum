#include "include/cube.h"

Cube::Cube(qreal x, qreal y, qreal w, qreal h, QColor color) :
    DynamicEntity(x, y, 100),
    _w(w),
    _h(h)
{
    setColor(color);
}

QRectF Cube::boundingRect() const
{
    return QRectF(_x, _y, _w, _h);
}

QPainterPath Cube::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _w, _h);
    return path;
}

void Cube::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(Qt::blue);
    pen.setWidth(5);
    painter->setPen(pen);
    painter->drawRect(_x, _y, _w, _h);
}

void Cube::move()
{

}
