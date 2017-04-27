#include "include/wall.h"
#include <QPen>

Wall::Wall(qreal x, qreal y, qreal w, qreal h, QColor color) :
    Entity(x, y),
    _w(w),
    _h(h)
{
    setColor(color);
}

QRectF Wall::boundingRect() const
{
    return QRectF(_x, _y, _w, _h);
}

QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _w, _h);
    return path;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Disable border drawing
    QPen pen(Qt::NoPen);
    painter->setPen(pen);

    // Drawing bricks
    painter->setBrush(_color);
    for (int i = 0, row = 0; i < _h; i += _brick_h, row++) {
        int j = 0;
        if (row % 2 == 1) {
            painter->drawRect(_x + 1, _y + i + 1, _brick_w / 2 - 1, _brick_h - 1);
            j = _brick_w / 2;
        }
        for (; j <= _w - _brick_w; j += _brick_w)
            painter->drawRect(_x + j + 1, _y + i + 1, _brick_w - 1, _brick_h - 1);
        if (j < _w)
            painter->drawRect(_x + j + 1, _y + i + 1, _brick_w / 2 - 1, _brick_h - 1);
    }
}
