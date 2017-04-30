#ifndef KEY_H
#define KEY_H

#include "include/entity.h"
#include "include/door.h"
#include "include/colors.h"

class Key : public Entity
{
public:
    Key(qreal x, qreal y, Door *door, const QColor color = SpectrumColors::gray);

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void unlockDoor();
    void lockDoor();
    Door* door() const;

private:
    const int _w = 25;
    const int _h = 45;
    Door *_door;
};

#endif // KEY_H
