#include "include/colorunlocker.h"

ColorUnlocker::ColorUnlocker(qreal x, qreal y, const QColor color) :
    Entity(x, y, color),
    _angle(0),
    _rotateTicker(new QTimer())
{
    connect(&(*_rotateTicker), SIGNAL(timeout()), this, SLOT(incrementAngle()));
    _rotateTicker->start(20);
}

QRectF ColorUnlocker::boundingRect() const
{
    return QRectF(_x, _y, _w, _h);
}

QPainterPath ColorUnlocker::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _w, _h);
    return path;
}

void ColorUnlocker::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(_x, _y, _w, _h);
    QPen pen(Qt::NoPen);
    painter->setPen(pen);
    painter->setBrush(QBrush(_color));
    QPoint points[] = {
        QPoint(_x, _y),
        QPoint(_x + _w/4, _y + _h),
        QPoint(_x + 3*_w/4, _y + _h),
        QPoint(_x + _w, _y),
        QPoint(_x, _y)
    };
    painter->drawPolygon(points, 5);
}

void ColorUnlocker::incrementAngle()
{
    _angle += 5;
}
