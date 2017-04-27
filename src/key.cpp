#include "include/key.h"

Key::Key(qreal x, qreal y, QColor color) :
    Entity(x, y, color)
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
    // Disable border drawing
    QPen pen(Qt::NoPen);
    painter->setPen(pen);

    // Drawing key
    painter->setBrush(_color);
    painter->drawRect(_x, _y, _w/3, _h);
    painter->drawRect(_x + _w/2 - 5, _y + _h/7, _w/2, _h/6);
    painter->drawRect(_x + _w/2 - 5, _y + 5*_h/12, _w/5, _h/6);
    painter->drawRect(_x - _w/8 - 1, _y + 5*_h/6 + 1, 6*_w/8, _h/6);

}
