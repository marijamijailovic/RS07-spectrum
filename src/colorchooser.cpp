#include "include/colorchooser.h"
#include "include/colors.h"


ColorChooser::ColorChooser(qreal x, qreal y, const bool *unlockedColors) :
    Entity(x, y, 200, 200, SpectrumColors::gray, false),
    _unlockedColors(unlockedColors)
{
    setZValue(1);
}

QRectF ColorChooser::boundingRect() const
{
    return QRectF(-_w/2, -_h/2, _w, _h);
}

QPainterPath ColorChooser::shape() const
{
    QPainterPath path;
    path.addRect(-_w/2, -_h/2, _w, _h);
    return path;
}

void ColorChooser::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPoint outer[7];
    QPoint inner[7];
    for (int i = 0, angle = 0; i < 7; i++, angle += 60) {
        outer[i] = QPoint(_w/2 * cos(angle * M_PI/180),
                          _h/2 * sin(angle * M_PI/180));
        inner[i] = QPoint(_w/3 * cos(angle * M_PI/180),
                          _h/3 * sin(angle * M_PI/180));
    }

    for (int i = 0; i < 6; i++) {
        if (_unlockedColors[i])
            painter->setBrush(QBrush(SpectrumColors::getColorFromID(i)));
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

int ColorChooser::determineColorID(QPointF &mouseReleasePos) const
{
    QPointF center(x(), y());
    QPointF offset(x() + 150, y());
    QLineF horizontal(center, offset);
    QLineF slope(center, mouseReleasePos);
    return 5 - (int)horizontal.angleTo(slope) / 60;
}
