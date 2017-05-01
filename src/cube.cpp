#include "include/cube.h"

Cube::Cube(qreal x, qreal y, qreal size, const QColor color) :
    DynamicEntity(x, y, 100, color),
    _size(size)
{

}

QRectF Cube::boundingRect() const
{
    return QRectF(_x, _y, _size, _size);
}

QPainterPath Cube::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _size, _size);
    return path;
}

void Cube::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Draw frame
    QPen pen(_color);
    pen.setWidth(5);
    painter->setPen(pen);
    painter->drawRect(_x, _y, _size, _size);

    // Draw crosses
    painter->drawLine(QPointF(_x + 2, _y + 2), QPointF(_x + _size - 2, _y + _size - 2));
    painter->drawLine(QPointF(_x + 2, _y + _size - 2), QPointF(_x + _size - 2, _y + 2));
}

void Cube::move(const QColor activeColor)
{

}
