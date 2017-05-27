#include "include/laser.h"
#include "include/player.h"
#include <typeinfo>


Laser::Laser(qreal x, qreal y,
             qreal dx,
             const QColor color) :
    Entity(x, y, dx > 0 ? dx : 5, 5, color, false),
    _step(1),
    _laserPos(0)
{
    if (dx != 5) {
        _moveTicker.reset(new QTimer());
        connect(&(*_moveTicker), SIGNAL(timeout()), this, SLOT(move()));
        _moveTicker->start(50);
    }
}

QRectF Laser::boundingRect() const
{
    return QRectF(_laserPos, 0, 5, 1000);
}

QPainterPath Laser::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _w, _h);
    path.addRect(_laserPos, 0, 5, 1000);
    return path;
}

void Laser::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillRect(0, 0, _w, _h, SpectrumColors::black);
    painter->fillRect(_laserPos, 0, 5, calculateLaserLength(), _color);
    painter->fillRect(_laserPos - 5, 0, 15, 15, SpectrumColors::black);
}

void Laser::move()
{
    if (_laserPos < 0 || _laserPos + 10 > _w)
        _step = -_step;
    _laserPos += _step;
}

qreal Laser::calculateLaserLength()
{
    qreal closestItemDistance = 1000;
    Entity *closestItem = NULL;
    auto collidingObjects = collidingItems();
    foreach (auto item, collidingObjects) {
        auto it = (Entity*)item;
        if (it->collidable()) {
            qreal top = it->pos().y();
            if (top < closestItemDistance) {
                closestItemDistance = top - y();
                closestItem = it;
            }
        }
    }

    if (closestItem && typeid(*closestItem) == typeid(Player))
        emit playerHit();

    return closestItemDistance;
}
