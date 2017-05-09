#include "include/door.h"

Door::Door(qreal x, qreal y, const QColor color, bool locked) :
    Entity(x, y, color, false),
    _locked(locked)
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

    // Drawing door
    painter->setBrush(_color);
    painter->drawRect(_x, _y + _w/2, _w, _h - _w/2);
    painter->drawChord(_x, _y, _w, _w, 0, 180 * 16);
    // If the door is locked then draw a lock as well
    /*if (_locked) {
        painter->setBrush(SpectrumColors::gray);
        // TODO draw a nice lock
        painter->drawRect(_x, _y + _h/3, _w, _h/10);
    }*/
}

void Door::unlock()
{
    _locked = false;
}

void Door::lock()
{
    _locked = true;
}
