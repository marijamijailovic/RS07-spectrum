#ifndef LADDER_H
#define LADDER_H

#include <QColor>
#include "include/colors.h"
#include "include/entity.h"


class Ladder : public Entity
{
public:
    Ladder(qreal x, qreal y, qreal w, qreal h, const QColor color = SpectrumColors::gray);

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    static constexpr qreal _step = 5;
    qreal _w;
    qreal _h;
};

#endif // LADDER_H
