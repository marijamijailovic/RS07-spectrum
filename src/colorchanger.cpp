#include "include/colorchanger.h"


ColorChanger::ColorChanger(QGraphicsView *view, qreal x, qreal y, QColor color) :
    Entity(x, y, SpectrumColors::gray, false),
    _r(50),
    _view(view),
    _color(color),
    _expandTicker(new QTimer())
{
    setZValue(-1);
    connect(_expandTicker.data(), SIGNAL(timeout()), this, SLOT(expand()));
    _expandTicker->start(15);
}

QRectF ColorChanger::boundingRect() const
{
    return QRectF(0, 0, _r, _r);
}

QPainterPath ColorChanger::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _r, _r);
    return path;
}

void ColorChanger::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(_color));
    painter->drawEllipse(0, 0, _r, _r);
}

void ColorChanger::expand()
{
    if (_r <= 1500) {
        _r += 50;
        update(0, 0, _r, _r);
        _view->update();
    } else {
        _expandTicker->stop();
        emit expandingDone();
    }
}

