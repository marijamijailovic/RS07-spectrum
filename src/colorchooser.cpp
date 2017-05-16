#include "include/colorchooser.h"
#include "include/colors.h"

ColorChooser::ColorChooser(qreal x, qreal y) :
    Entity(x, y, SpectrumColors::gray, false),
    _r(0),
    _step(5),
    _expandTicker(new QTimer()),
    _shrinkTicker(new QTimer())
{
    connect(&(*_expandTicker), SIGNAL(timeout()), this, SLOT(increment()));
    connect(&(*_shrinkTicker), SIGNAL(timeout()), this, SLOT(decrement()));
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
    painter->drawRect(_x, _y, _r, _r);
}

void ColorChooser::relocate(qreal x, qreal y)
{
    _x = x;
    _y = y;
}

void ColorChooser::expand()
{
    _shrinkTicker->stop();
    _expandTicker->start(50);
}

void ColorChooser::shrink()
{
    _expandTicker->stop();
    _shrinkTicker->start(50);
}

void ColorChooser::increment()
{
    _r += _step;
    if (_r > 195)
        _expandTicker->stop();
}

void ColorChooser::decrement()
{
    _r -= _step;
    if (_r < 5)
        _shrinkTicker->stop();
}
