#include "include/ladder.h"

Ladder::Ladder(qreal x, qreal y, qreal w, qreal h, const QColor color) :
    Entity(x, y, color, true),
    _w(w),
    _h(h)
{

}

QRectF Ladder::boundingRect() const
{
    return QRectF(0, 0, _w, _h);
}

QPainterPath Ladder::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _w, _h);
    return path;
}

void Ladder::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Disable border drawing
    QPen pen(Qt::NoPen);
    painter->setPen(pen);

    // Drawing steps
    painter->setBrush(_color);
    for (int i = 10; i < _h; i += 20)
        painter->drawRect(0, i, _w, 5);

    // Drawing sides
    painter->drawRect(0, 0, 5, _h);
    painter->drawRect(_w - 5, 0, 5, _h);
}
