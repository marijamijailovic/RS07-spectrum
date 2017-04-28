#ifndef DOOR_H
#define DOOR_H

#include "include/colors.h"
#include "include/entity.h"

class Door : public Entity
{
public:
    Door(qreal x, qreal y, const QColor color = SpectrumColors::gray);

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    const int _w = 60;
    const int _h = 100;
};

#endif // DOOR_H
