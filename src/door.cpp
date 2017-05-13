#include "include/door.h"

Door::Door(qreal x, qreal y, const QString &nextLevel, const QColor color, bool locked) :
    Entity(x, y, color, false),
    _barH(_h - _w/12),
    _locked(locked),
    _drawBars(locked),
    _barShrinkTicker(new QTimer()),
    _nextLevel(nextLevel)
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

    // Drawing bars
    if (_drawBars) {
        // Left
        painter->drawRoundedRect(_x + _w/4 - 2, _y + _w/12, 4, _barH, 3, 3);
        // Right
        painter->drawRoundedRect(_x + _w/2 - 2, _y, 4, _barH + _w/12, 3, 3);
        // Middle
        painter->drawRoundedRect(_x + 3*_w/4 - 2, _y + _w/12, 4, _barH, 3, 3);
    }

    // Drawing door lock
    if (_locked) {
        QPen p(SpectrumColors::gray);
        p.setWidth(2);
        painter->setPen(p);
        painter->drawArc(_x + _w - 10, _y + _h/2, 10, 10, 0, 180 * 16);
        painter->drawRoundedRect(_x + _w - 10, _y + _h/2 + 5, 10, 10, 3, 3);
    }
}

void Door::lock()
{
    _locked = true;
    _drawBars = true;
    _barH = _h - _w/12;
}

void Door::unlock()
{
    _locked = false;
    _barShrinkTicker->start(40);
}

QString Door::nextLevel() const
{
    return _nextLevel;
}

void Door::shrinkBars()
{
    if (_barH > 0)
        _barH -= 5;
    else {
        _drawBars = false;
        _barShrinkTicker->stop();
        _barH = 0;
    }
}

