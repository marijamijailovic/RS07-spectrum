#include "include/cube.h"
Cube::Cube(qreal x, qreal y, qreal size, const QColor color) :
    DynamicEntity(x, y, 1, color),
    _size(size)
{

}

QRectF Cube::boundingRect() const
{
    return QRectF(0, 0, _size, _size);
}

QPainterPath Cube::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _size, _size);
    return path;
}

void Cube::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Draw frame
    painter->fillRect(0, 0, 5, _size, _color);
    painter->fillRect(_size - 5, 0, 5, _size, _color);
    painter->fillRect(0, 0, _size, 5, _color);
    painter->fillRect(0, _size - 5, _size, 5, _color);

    // Draw crosses
    QPen pen(_color);
    pen.setWidth(5);
    painter->setPen(pen);
    painter->drawLine(QPointF(3, 3), QPointF(_size - 3, _size - 3));
    painter->drawLine(QPointF(3, _size - 3), QPointF(_size - 3, 3));
}

void Cube::move()
{
    int vy = (int)_vy;
    for(int i = 1; i <= vy; i++) {
        moveBy(0, 1);

        int ignoredCollisions = 0;
        auto collidingObjects = collidingItems();
        foreach (QGraphicsItem *item, collidingObjects)
            if (!((Entity*)item)->collidable())
                ignoredCollisions++;

        if (collidingObjects.size() > ignoredCollisions) {
            moveBy(0, -i);
            _vy = 0;
            //_y += i;
            break;
        }
    }
}
