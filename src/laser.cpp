#include "include/laser.h"


Laser::Laser(qreal x, qreal y,
             qreal dx,
             const QColor color) :
    Entity(x, y, dx > 0 ? dx : 5, 5, color, true),
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
    QPen pen(Qt::NoPen);
    painter->setPen(pen);
    painter->setBrush(QBrush(_color));
    painter->drawRect(0, 0, _w, _h);
    painter->drawRect(_laserPos, 0, 5, calculateLaserLength());
}

void Laser::move()
{
    _laserPos += _step;
    if (_laserPos == 0 || _laserPos == _w)
        _step = -_step;
}

#include <QDebug>
qreal Laser::calculateLaserLength() const
{
    qreal closestItemDistance = 1000;
    auto collidingObjects = collidingItems();
    foreach (auto item, collidingObjects) {
        //if (typeid(*item) == typeid(Player))
        //    emit playerHit();
        auto it = (Entity*)item;
        if (it->collidable()) {
            // Determine if laser hits from above or below
            qreal top = it->pos().y();
            qDebug() << "top: " << top;
            qDebug() << "y  : " << y();
            if (top < closestItemDistance)
                closestItemDistance = top - y();
        }
    }

    return closestItemDistance;
}
