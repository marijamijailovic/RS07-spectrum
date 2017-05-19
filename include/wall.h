#ifndef WALL_H
#define WALL_H

#include <QColor>
#include "include/entity.h"
#include "include/colors.h"


class Wall : public Entity
{
public:
    Wall(qreal x, qreal y, qreal w, qreal h,
         const QColor color = SpectrumColors::gray);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    const qreal _brick_w = 20;
    const qreal _brick_h = 10;
};

#endif // WALL_H
