#ifndef SPIKE_H
#define SPIKE_H

#include "include/entity.h"


class Spike : public Entity
{
public:
    Spike(qreal x, qreal y, qreal w, qreal h);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // SPIKE_H
