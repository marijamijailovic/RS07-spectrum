#ifndef KEY_H
#define KEY_H

#include "include/entity.h"
#include "include/colors.h"

class Key : public Entity
{
public:
    Key(qreal x, qreal y, const QColor color = SpectrumColors::gray);

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    const int _w = 25;
    const int _h = 45;
};

#endif // KEY_H
