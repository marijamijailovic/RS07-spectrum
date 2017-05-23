#ifndef CUBE_H
#define CUBE_H

#include "include/dynamicentity.h"


class Cube : public DynamicEntity
{
public:
    Cube(qreal x, qreal y, qreal size,
         const QColor color = SpectrumColors::gray);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    // Overrides from DynamicEntity
    void move();
};

#endif // CUBE_H
