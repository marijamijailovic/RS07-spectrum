#include "include/key.h"

Key::Key(qreal x, qreal y, Door *door, const QColor color) :
    Entity(x, y, color),
    _door(door),
    _sparkTicker(new QTimer())
{
    connect(&(*_sparkTicker), SIGNAL(timeout()), this, SLOT(updateSparklesPos()));
    _sparkTicker->start(250);
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
    QPen pen(_color);
    pen.setWidth(3);
    painter->setPen(pen);

    // Drawing key
    painter->drawArc(_x, _y + _h/3, _h/2, _h/2, 0, 360 * 16);
    painter->fillRect(_x + _h/2, _y + _h/2, _w - _h/2, 3, _color);
    painter->fillRect(_x + 3*_w/4, _y + _h/2, 3, 7, _color);
    painter->fillRect(_x + _w - 3, _y + _h/2, 3, 10, _color);

    // Sparkles
    pen.setWidth(1);
    painter->setPen(pen);
    for (unsigned i = 0; i < _sparkNum; i++)
        painter->drawEllipse(_sx[i], _sy[i], 1, 1);
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

void Key::updateSparklesPos()
{
    for (unsigned i = 0; i < _sparkNum; i++)
        _sx[i] = _x + qrand() % _w;
    for (unsigned i = 0; i < _sparkNum; i++)
        _sy[i] = _y + qrand() % _h;
}
