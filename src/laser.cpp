#include "include/laser.h"


Laser::Laser(qreal x, qreal y,
             qreal dx, qreal dy,
             const QColor color) :
    Entity(x, y, dx > 0 ? dx : 5, dy > 0 ? dy : 5, color, true),
    _step(1),
    _laserPos(0)
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
    QPen pen(Qt::NoPen);
    painter->setPen(pen);
    painter->setBrush(QBrush(_color));
    painter->drawRect(0, 0, _w, _h);
    if (_w != 5)
        painter->drawRect(_laserPos, 0, 5, calculateLaserLength());
    else
        painter->drawRect(0, _laserPos, calculateLaserLength(), 5);
}

void Laser::move()
{
    _laserPos += _step;
    if (_w != 5 && (_laserPos == 0 || _laserPos == _w))
        _step = -_step;
    if (_h != 5 && (_laserPos == 0 || _laserPos == _h))
        _step = -_step;
}

qreal Laser::calculateLaserLength() const
{
    return 100;     // TODO
}
