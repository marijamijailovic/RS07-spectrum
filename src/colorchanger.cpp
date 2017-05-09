#include "include/colorchanger.h"

ColorChanger::ColorChanger(QGraphicsView *view, qreal x, qreal y, QColor color) :
    _x(x),
    _y(y),
    _r(50),
    _view(view),
    _color(color),
    _expandTicker(new QTimer())
{
    setZValue(-1);
    connect(_expandTicker.data(), SIGNAL(timeout()), this, SLOT(expand()));
    _expandTicker->start(10);
}

QRectF ColorChanger::boundingRect() const
{
    return QRectF(_x, _y, _r, _r);
}

QPainterPath ColorChanger::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _r, _r);
    return path;
}

void ColorChanger::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(_color));
    painter->drawEllipse(_x - _r/2, _y - _r/2, _r, _r);
}

void ColorChanger::expand()
{
    if (_r <= 2000) {
        _r += 100;
        update(_x, _y, _r, _r);
        _view->update();
    } else
        _expandTicker->stop();
}

void ColorChanger::run()
{
    _expandTicker->start(20);
}
