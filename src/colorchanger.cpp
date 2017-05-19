#include "include/colorchanger.h"


ColorChanger::ColorChanger(QGraphicsView *view, qreal x, qreal y, QColor color) :
    Entity(x, y, 50, 50, color, false),
    _view(view),
    _expandTicker(new QTimer())
{
    setZValue(-1);
    connect(_expandTicker.data(), SIGNAL(timeout()), this, SLOT(expand()));
    _expandTicker->start(15);
}

void ColorChanger::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(_color));
    painter->drawEllipse(0, 0, _w, _h);
}

void ColorChanger::expand()
{
    if (_w <= 1500) {
        _w += 50;
        _h += 50;
        update(0, 0, _w, _h);
        _view->update();
    } else {
        _expandTicker->stop();
        emit expandingDone();
    }
}

