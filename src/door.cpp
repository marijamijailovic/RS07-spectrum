#include "include/door.h"

Door::Door(qreal x, qreal y, QColor color) :
    Entity(x, y, color)
{

}

QRectF Door::boundingRect() const
{
    return QRectF(_x, _y, _w, _h);
}

QPainterPath Door::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _w, _h);
    return path;
}

void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Disable border drawing
    QPen pen(Qt::NoPen);
    painter->setPen(pen);

    // Drawing key
    painter->setBrush(_color);
    painter->drawRect(_x, _y, _w, 3*_h/4);
    painter->drawEllipse(QPoint(_x + _w/2, _y - _h/2 + _w - 3), _w/2, _w/2);

}
