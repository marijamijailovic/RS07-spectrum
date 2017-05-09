#include "include/key.h"

Key::Key(qreal x, qreal y, Door *door, const QColor color) :
    Entity(x, y, color),
    _door(door)
{

}

QRectF Key::boundingRect() const
{
    return QRectF(_x, _y, _w, _h);
}

QPainterPath Key::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _w, _h);
    return path;
}

void Key::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->drawRect(_x, _y, _w, _h);

    QPen pen(_color);
    pen.setWidth(3);
    painter->setPen(pen);

    // Drawing key
    painter->drawArc(_x, _y + _h/3, _h/2, _h/2, 0, 360 * 16);
    painter->fillRect(_x + _h/2, _y + _h/2, _w - _h/2, 3, _color);
    painter->fillRect(_x + 3*_w/4, _y + _h/2, 3, 7, _color);
    painter->fillRect(_x + _w - 3, _y + _h/2, 3, 10, _color);
}

void Key::unlockDoor()
{
    _door->unlock();
}

void Key::lockDoor()
{
    _door->lock();
}

Door* Key::door() const
{
    return _door;
}
