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
    return QRectF(0, 0, _r, _r);
}

QPainterPath ColorChooser::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _r, _r);
    return path;
}

void ColorChooser::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(0, 0, _r, _r);
}
