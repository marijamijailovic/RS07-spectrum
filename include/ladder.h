#ifndef LADDER_H
#define LADDER_H

#include <QColor>
#include "include/colors.h"
#include "include/entity.h"


class Ladder : public Entity
{
public:
    Ladder(qreal x, qreal y, qreal w, qreal h,
           const QColor color = SpectrumColors::gray);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    const qreal _step = 5;
};

#endif // LADDER_H
