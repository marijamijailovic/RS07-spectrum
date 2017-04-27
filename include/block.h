#ifndef BLOCK_H
#define BLOCK_H

#include "include/entity.h"


class Block : public Entity
{
public:
    Block(qreal x, qreal y, qreal w, qreal h, QColor color = Qt::gray);

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    const qreal _brick_w = 20;
    const qreal _brick_h = 10;
    qreal _w;
    qreal _h;
};

#endif // BLOCK_H
