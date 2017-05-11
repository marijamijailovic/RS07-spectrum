#include "include/cube.h"
Cube::Cube(qreal x, qreal y, qreal size, const QColor color) :
    DynamicEntity(x, y, 1, color),
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
    painter->fillRect(_x, _y, 5, _size, _color);
    painter->fillRect(_x + _size - 5, _y, 5, _size, _color);
    painter->fillRect(_x, _y, _size, 5, _color);
    painter->fillRect(_x, _y + _size - 5, _size, 5, _color);

    // Draw crosses
    QPen pen(_color);
    pen.setWidth(5);
    painter->setPen(pen);
    painter->drawLine(QPointF(_x + 3, _y + 3), QPointF(_x + _size - 3, _y + _size - 3));
    painter->drawLine(QPointF(_x + 3, _y + _size - 3), QPointF(_x + _size - 3, _y + 3));
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
