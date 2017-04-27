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
    // Drawing bricks
    int row = 0;
    for (int i = 0; i < _h; i += 10, row++) {
        int j = 0;
        if (row % 2 == 1) {
            painter->fillRect(_x + 1, _y + i + 1, 9, 9, _color);
            j = 10;
        }
        for (; j <= _w - 20; j += 20)
            painter->fillRect(_x + j + 1, _y + i + 1, 19, 9, _color);
        if (j < _w)
            painter->fillRect(_x + j + 1, _y + i + 1, 9, 9, _color);
    }
}
