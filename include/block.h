#ifndef BLOCK_H
#define BLOCK_H

#include <QtGlobal>
#include <QGraphicsRectItem>
#include "include/entity.h"


class Block : public Entity, public QGraphicsRectItem
{
public:
    Block(qreal x, qreal y, qreal h, qreal w);

    void drawAt(qreal x, qreal y);
};

#endif // BLOCK_H
