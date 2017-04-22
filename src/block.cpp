#include "include/block.h"

Block::Block(qreal x, qreal y, qreal h, qreal w) :
    Entity(x, y),
    QGraphicsRectItem(x, y, h, w)
{

}

void Block::drawAt(qreal x, qreal y)
{
    _x = x;
    _y = y;
    setPos(x, y);
}
