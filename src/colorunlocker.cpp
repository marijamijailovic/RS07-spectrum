#include "include/colorunlocker.h"


ColorUnlocker::ColorUnlocker(qreal x, qreal y, const QColor color) :
    Entity(x, y, 60, 30, color, true),
    _opacity(225),
    _step(5),
    _raiseH(0),
    _opacityTicker(new QTimer()),
    _raiseTicker(new QTimer())
{
    connect(&(*_opacityTicker), SIGNAL(timeout()), this, SLOT(incrementOpacity()));
    connect(&(*_raiseTicker), SIGNAL(timeout()), this, SLOT(raise()));
    _opacityTicker->start(25);
}

void ColorUnlocker::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(Qt::NoPen);
    painter->setPen(pen);
    _color.setAlpha(_opacity);
    painter->setBrush(QBrush(_color));
    painter->drawRect(0, 0, _w, _h);
    /*
    QPoint points[] = {
        QPoint(-_w/2, -_h/2 - _raiseH),
        QPoint(-_w/2 + _w/4, _y + _h - _raiseH),
        QPoint(_x + 3*_w/4, _y + _h - _raiseH),
        QPoint(_x + _w, _y - _raiseH),
        QPoint(_x, _y - _raiseH)
    };
    painter->drawPolygon(points, 5);*/
}

void ColorUnlocker::collect()
{
    _raiseTicker->start(40);
    _collidable = false;
    emit colorUnlocked(SpectrumColors::toEnum(_color));
}

void ColorUnlocker::incrementOpacity()
{
    _opacity += _step;
    if (_opacity > 250 || _opacity < 200)
        _step = -_step;
}

void ColorUnlocker::raise()
{
    if (_raiseH < 50)
        _raiseH += 5;
    else {
        _raiseTicker->stop();
        hide();
        _raiseH = 0;
    }
}
