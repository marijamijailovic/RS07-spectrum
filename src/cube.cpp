#include "include/cube.h"

Cube::Cube(qreal x, qreal y, qreal size, QColor color) :
    DynamicEntity(x, y, 100),
    _size(size)
{
    setColor(color);
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
    QPen pen(Qt::blue);
    pen.setWidth(5);
    painter->setPen(pen);
    painter->drawRect(_x, _y, _size, _size);
    painter->translate(_x + _size/2, _y + _size/2);
    painter->rotate(45);
    painter->fillRect(-_size/2, -2, _size, 5, Qt::blue);
    painter->rotate(-90);
    painter->fillRect(-_size/2, -2, _size, 5, Qt::blue);
}

void Cube::move()
{

}
