#include "include/door.h"

Door::Door(qreal x, qreal y, const QColor color, bool locked) :
    Entity(x, y, color, false),
    _barH(_h),
    _locked(locked),
    _drawBars(locked),
    _barShrinkTicker(new QTimer())
{
    connect(&(*_barShrinkTicker), SIGNAL(timeout()), this, SLOT(shrinkBars()));
}

QRectF Door::boundingRect() const
{
    return QRectF(_x, _y, _w, _h);
}

QPainterPath Door::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _w, _h);
    return path;
}

void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Disable border drawing
    QPen pen(Qt::NoPen);
    painter->setPen(pen);

    // Drawing door
    painter->setBrush(_color);
    painter->drawRect(_x, _y + _w/2, _w, _h - _w/2);
    painter->drawChord(_x, _y, _w, _w, 0, 180 * 16);


    painter->setBrush(SpectrumColors::gray);

    if (_drawBars) {
        painter->drawRect(_x + _w/4 - 2, _y + _w/12, 4, _barH - _w/12);
        painter->drawRect(_x + _w/2 - 2, _y, 4, _barH);
        painter->drawRect(_x + 3*_w/4 - 2, _y + _w/12, 4, _barH - _w/12);
    }

    if (_locked) {
        QPen p(SpectrumColors::gray);
        p.setWidth(2);
        painter->setPen(p);
        painter->drawArc(_x + _w - 10, _y + _h/2, 10, 10, 0, 180 * 16);
        painter->drawRect(_x + _w - 10, _y + _h/2 + 5, 10, 10, SpectrumColors::gray);
    }
}

void Door::lock()
{
    _locked = true;
    _drawBars = true;
    _barH = _h;
}

void Door::unlock()
{
    _locked = false;
    _barShrinkTicker->start(20);
}

void Door::shrinkBars()
{
    if (_barH > 0)
        _barH -= 5;
    else {
        _drawBars = false;
        _barShrinkTicker->stop();
    }
}

