#ifndef BLOCK_H
#define BLOCK_H

#include <QColor>
#include "include/colors.h"
#include "include/entity.h"


class Block : public Entity
{
public:
    Block(qreal x, qreal y, qreal w, qreal h);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // BLOCK_H
