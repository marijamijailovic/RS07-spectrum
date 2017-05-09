#include "include/door.h"

Door::Door(qreal x, qreal y, const QString &nextLevel, const QColor color, bool locked) :
    Entity(x, y, color, false),
    _locked(locked)
{
    _nextLevel = nextLevel;
}

QRectF Door::boundingRect() const
{
    return QRectF(_x, _y - _h/2 + _w/2 -3, _w, 3*_h/2-_w/2 + 3);
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
    painter->setBrush(_color);`
    painter->drawRect(_x, _y, _w, 3*_h/4);
    painter->drawEllipse(QPoint(_x + _w/2, _y - _h/2 + _w - 3), _w/2, _w/2);
    // If the door is locked then draw a lock as well
    if (_locked) {
        painter->setBrush(SpectrumColors::gray);
        // TODO draw a nice lock
        painter->drawRect(_x, _y + _h/3, _w, _h/10);
    }
}

QString Door::nextLevel() const
{
    return _nextLevel;
}

void Door::unlock()
{
    _locked = false;
}

void Door::lock()
{
    _locked = true;
}
