#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "include/entity.h"


class Background : public Entity
{
public:
    Background();

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // BACKGROUND_H
