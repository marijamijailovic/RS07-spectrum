#include "include/cube.h"
Cube::Cube(qreal x, qreal y, qreal size, const QColor color) :
    DynamicEntity(x, y, size, size, 1, color, true)
{

}

void Cube::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Draw frame
    painter->fillRect(0, 0, 5, _h, _color);
    painter->fillRect(_w - 5, 0, 5, _h, _color);
    painter->fillRect(0, 0, _w, 5, _color);
    painter->fillRect(0, _h - 5, _w, 5, _color);

    // Draw crosses
    QPen pen(_color);
    pen.setWidth(5);
    painter->setPen(pen);
    painter->drawLine(QPointF(3, 3), QPointF(_w - 3, _h - 3));
    painter->drawLine(QPointF(3, _h - 3), QPointF(_w - 3, 3));
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
