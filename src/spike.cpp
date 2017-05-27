#include "include/spike.h"

Spike::Spike(qreal x, qreal y, qreal w, qreal h) :
    Entity(x, y, w, h, SpectrumColors::black, false)
{

}

void Spike::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(0, 0, _w, _h);
}
