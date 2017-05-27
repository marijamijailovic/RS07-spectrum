#include "include/laser.h"
#include "include/player.h"
#include <typeinfo>


Laser::Laser(qreal x, qreal y,
             qreal dx, qreal dy,
             Direction direction,
             const QColor color) :
    Entity(x, y, 0, 0, color, false),
    _direction(direction),
    _hidden(false),
    _step(1),
    _laserPos(10)
{
    if (direction == UP || direction == DOWN) {
        _w = dx;
        _h = 10;
    } else {
        _w = 10;
        _h = dy;
    }

    // If laser is set to move, then register timer for it
    if (dx != 0 || dy != 0) {
        _moveTicker.reset(new QTimer());
        connect(&(*_moveTicker), SIGNAL(timeout()), this, SLOT(move()));
        _moveTicker->start(50);
    }
}

QRectF Laser::boundingRect() const
{
    if (_direction == UP)
        return QRectF(_laserPos, 0, LASER_WIDTH, -MAX_LASER_LEN);
    else if (_direction == DOWN)
        return QRectF(_laserPos, 0, LASER_WIDTH, MAX_LASER_LEN);
    else if (_direction == LEFT)
        return QRectF(0, _laserPos, -MAX_LASER_LEN, LASER_WIDTH);
    else // if (_direction == RIGHT)
        return QRectF(0, _laserPos, MAX_LASER_LEN, LASER_WIDTH);
}

QPainterPath Laser::shape() const
{
    QPainterPath path;

    if (_direction == UP) {
        path.addRect(0, 0, _w, 10);
        path.addRect(_laserPos, 0, LASER_WIDTH, -MAX_LASER_LEN);
    } else if (_direction == DOWN) {
        path.addRect(0, 0, _w, 10);
        path.addRect(_laserPos, 0, LASER_WIDTH, MAX_LASER_LEN);
    } else if (_direction == LEFT) {
        path.addRect(0, 0, 10, _h);
        path.addRect(0, _laserPos, -MAX_LASER_LEN, LASER_WIDTH);
    } else { // if (_direction == RIGHT)
        path.addRect(0, 0, 10, _h);
        path.addRect(0, _laserPos, MAX_LASER_LEN, LASER_WIDTH);
    }

    return path;
}

void Laser::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (_hidden)
        return;

    if (_direction == UP) {
        painter->fillRect(0, 0, _w, 10, SpectrumColors::black);
        painter->fillRect(_laserPos, 0, LASER_WIDTH, -calculateLaserLength(), _color);
        painter->fillRect(_laserPos - 5, -5, 15, 15, SpectrumColors::black);
        painter->fillRect(_laserPos - 5, 8, 15, 2, _color);
    } else if (_direction == DOWN) {
        painter->fillRect(0, 0, _w, 10, SpectrumColors::black);
        painter->fillRect(_laserPos, 10, LASER_WIDTH, calculateLaserLength(), _color);
        painter->fillRect(_laserPos - 5, 0, 15, 15, SpectrumColors::black);
        painter->fillRect(_laserPos - 5, 0, 15, 2, _color);
    } else if (_direction == LEFT) {
        painter->fillRect(0, 0, 10, _h, SpectrumColors::black);
        painter->fillRect(0, _laserPos, -calculateLaserLength(), LASER_WIDTH, _color);
        painter->fillRect(-5, _laserPos - 5, 15, 15, SpectrumColors::black);
        painter->fillRect(8, _laserPos - 5, 2, 15, _color);
    } else { // if (_direction == RIGHT)
        painter->fillRect(0, 0, 10, _h, SpectrumColors::black);
        painter->fillRect(10, _laserPos, calculateLaserLength(), LASER_WIDTH, _color);
        painter->fillRect(0, _laserPos - 5, 15, 15, SpectrumColors::black);
        painter->fillRect(0, _laserPos - 5, 2, 15, _color);
    }
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
    qreal limit = _w > _h ? _w : _h;
    if (_laserPos + _step < 5 || _laserPos + _step > limit - 10)
        _step = -_step;
    _laserPos += _step;
}

qreal Laser::calculateLaserLength()
{
    return 100;
    /*
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

    return closestItemDistance;*/
}
