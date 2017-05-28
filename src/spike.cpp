#include "include/spike.h"
#include "include/player.h"


Spike::Spike(qreal x, qreal y, qreal w, qreal h) :
    Entity(x, y, w, h, SpectrumColors::black, false)
{

}

void Spike::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPainterPath path(QPoint(_w, _h));
    for (qreal dx = 0; dx <= _w; dx += 10) {
        path.lineTo(QPoint(dx, _h));
        path.lineTo(QPoint(dx + 5, 0));
    }
    painter->fillPath(path, SpectrumColors::black);

    if (collidesWithPlayer())
        emit playerHit();
}

bool Spike::collidesWithPlayer() const
{
    foreach (auto item, collidingItems())
        if (typeid(*item) == typeid(Player))
            return true;

    return false;
}
