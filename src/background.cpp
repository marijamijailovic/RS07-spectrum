#include "include/background.h"

Background::Background()
    : Entity(0, 0, Qt::gray, false)
{
    //setZValue(-1);
}

QRectF Background::boundingRect() const
{
    return QRectF(0, 0, 800, 600);
}

QPainterPath Background::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 800, 600);
    return path;
}

void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, 800, 600, QPixmap(":sprites/bg.png"));
}
