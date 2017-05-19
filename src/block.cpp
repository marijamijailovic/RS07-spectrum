#include "include/block.h"


Block::Block(qreal x, qreal y, qreal w, qreal h) :
    Entity(x, y, SpectrumColors::gray),
    _w(w),
    _h(h)
{

}

QRectF Block::boundingRect() const
{
    return QRectF(0, 0, _w, _h);
}

QPainterPath Block::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _w, _h);
    return path;
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen p(Qt::NoPen);
    painter->setPen(p);
    painter->setBrush(QBrush(QPixmap(":sprites/block.png")));
    painter->drawRect(0, 0, _w, _h);
}
