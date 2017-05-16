#include "include/colorchooser.h"
#include "include/colors.h"

ColorChooser::ColorChooser(qreal x, qreal y) :
    Entity(x, y, SpectrumColors::gray, false),
    _r(200)
{
    setZValue(1);
}

QRectF ColorChooser::boundingRect() const
{
    return QRectF(_x, _y, _r, _r);
}

QPainterPath ColorChooser::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _r, _r);
    return path;
}

void ColorChooser::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(_x - _r/2, _y - _r/2, _r, _r);
}

void ColorChooser::relocate(qreal x, qreal y)
{
    _x = x;
    _y = y;
}
