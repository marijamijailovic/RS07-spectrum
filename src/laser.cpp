#include "include/laser.h"


Laser::Laser(qreal x, qreal y,
             qreal dx, qreal dy,
             const QColor color) :
    Entity(x, y, dx > 0 ? dx : 5, dy > 0 ? dy : 5, color, true)
{
    if (dx != 5 || dy != 5) {
        _moveTicker.reset(new QTimer());
        connect(&(*_moveTicker), SIGNAL(timeout()), this, SLOT(move()));
        _moveTicker->start(50);
    }
}

QRectF Laser::boundingRect() const
{
    return QRectF(0, 0, _w, _h);
}

QPainterPath Laser::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _w, _h);
    return path;
}

void Laser::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(_color));
    painter->drawRect(0, 0, _w, _h);
}

void Laser::move()
{

}
