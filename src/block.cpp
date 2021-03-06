#include "include/block.h"


Block::Block(qreal x, qreal y, qreal w, qreal h) :
    Entity(x, y, w, h, SpectrumColors::gray, true),
    _texture(":sprites/block.png")
{

}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen p(Qt::NoPen);
    painter->setPen(p);
    painter->setBrush(QBrush(_texture));
    painter->drawRect(0, 0, _w, _h);
}
