#include "include/laser.h"
#include "include/player.h"
#include <typeinfo>


Laser::Laser(qreal x, qreal y,
             qreal dx,
             const QColor color) :
    Entity(x, y, dx > 0 ? dx : LASER_WIDTH, 10, color, false),
    _hidden(false),
    _step(1),
    _laserPos(0)
{
    if (dx != LASER_WIDTH) {
        _moveTicker.reset(new QTimer());
        connect(&(*_moveTicker), SIGNAL(timeout()), this, SLOT(move()));
        _moveTicker->start(50);
    }
}

QRectF Laser::boundingRect() const
{
    return QRectF(_laserPos, 0, LASER_WIDTH, MAX_LASER_LEN);
}

QPainterPath Laser::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _w, 10);
    path.addRect(_laserPos, 0, LASER_WIDTH, MAX_LASER_LEN);
    return path;
}

void Laser::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillRect(0, 0, _w, 10, SpectrumColors::black);
    if (!_hidden)
        painter->fillRect(_laserPos, 0, LASER_WIDTH, calculateLaserLength(), _color);
    painter->fillRect(_laserPos - LASER_WIDTH, 0, 15, 15, SpectrumColors::black);
    painter->fillRect(_laserPos - LASER_WIDTH, 5, 15, 2, _color);
}

void Laser::hide()
{
    _hidden = true;
}

void Laser::show()
{
    _hidden = false;
}

void Laser::move()
{
    if (_laserPos < 0 || _laserPos + 10 > _w)
        _step = -_step;
    _laserPos += _step;
}

qreal Laser::calculateLaserLength()
{
    qreal closestItemDistance = MAX_LASER_LEN;
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

    if (!_hidden && closestItem != NULL && typeid(*closestItem) == typeid(Player))
        emit playerHit();

    return closestItemDistance;
}
