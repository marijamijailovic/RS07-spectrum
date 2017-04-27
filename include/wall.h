#ifndef WALL_H
#define WALL_H

#include <QColor>
#include "include/entity.h"
#include "include/colors.h"


class Wall : public Entity
{
public:
    Wall(qreal x, qreal y, qreal w, qreal h, QColor color = SpectrumColors::gray);

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    static constexpr qreal _brick_w = 20;
    static constexpr qreal _brick_h = 10;
    qreal _w;
    qreal _h;
};

#endif // WALL_H
