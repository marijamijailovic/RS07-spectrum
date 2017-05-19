#include "include/colorchooser.h"
#include "include/colors.h"

ColorChooser::ColorChooser(qreal x, qreal y, const bool *unlockedColors) :
    Entity(x, y, SpectrumColors::gray, false),
    _r(200),
    _unlockedColors(unlockedColors)
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
    QPoint outer[7];
    QPoint inner[7];
    for (int i = 0, angle = 0; i < 7; i++, angle += 60) {
        outer[i] = QPoint(_x + _r/2 * cos(angle * M_PI/180),
                          _y + _r/2 * sin(angle * M_PI/180));
        inner[i] = QPoint(_x + _r/3 * cos(angle * M_PI/180),
                          _y + _r/3 * sin(angle * M_PI/180));
    }

    for (int i = 0; i < 6; i++) {
        if (_unlockedColors[i])
            painter->setBrush(QBrush(SpectrumColors::getColorId(i)));
        else
            painter->setBrush(QBrush(SpectrumColors::gray));
        QPainterPath path(outer[i]);
        path.lineTo(outer[i+1]);
        path.lineTo(inner[i+1]);
        path.lineTo(inner[i]);
        path.lineTo(outer[i]);
        painter->drawPath(path);
    }
}

void ColorChooser::relocate(qreal x, qreal y)
{
    _x = x;
    _y = y;
}
