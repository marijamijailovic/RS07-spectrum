#include "include/colorchooser.h"
#include "include/colors.h"

ColorChooser::ColorChooser(qreal x, qreal y) :
    Entity(x, y, 200, 200, SpectrumColors::gray, false)
{
    setZValue(1);
}

void ColorChooser::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // TODO
    (void)painter;
}
