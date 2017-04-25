#include "include/block.h"


Block::Block(qreal x, qreal y, qreal w, qreal h, QColor color) :
    Entity(x, y),
    _w(w),
    _h(h)
{
    setColor(color);
}

QRectF Block::boundingRect() const
{
    return QRectF(_x, _y, _w, _h);
}

QPainterPath Block::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _w, _h);
    return path;
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(_color);
    painter->drawRect(_x, _y, _w, _h);
}
