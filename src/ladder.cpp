#include "include/ladder.h"

Ladder::Ladder(qreal x, qreal y, qreal w, qreal h, QColor color) :
    Entity(x, y),
    _w(w),
    _h(h)
{
    setColor(color);
}

QRectF Ladder::boundingRect() const
{
    return QRectF(_x, _y, _w, _h);
}

QPainterPath Ladder::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _w, _h);
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
        painter->drawRect(_x, _y + i, _w, 5);

    // Drawing sides
    painter->drawRect(_x, _y, 5, _h);
    painter->drawRect(_x + _w - 5, _y, 5, _h);
}
