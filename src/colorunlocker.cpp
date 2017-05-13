#include "include/colorunlocker.h"

ColorUnlocker::ColorUnlocker(qreal x, qreal y, const QColor color) :
    Entity(x, y, color),
    _opacity(225),
    _step(5),
    _opacityTicker(new QTimer())
{
    connect(&(*_opacityTicker), SIGNAL(timeout()), this, SLOT(incrementOpacity()));
    _opacityTicker->start(25);
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
    _color.setAlpha(_opacity);
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

void ColorUnlocker::incrementOpacity()
{
    _opacity += _step;
    if (_opacity > 255 || _opacity < 200)
        _step = -_step;
}
