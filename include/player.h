#ifndef PLAYER_H
#define PLAYER_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include "include/dynamicentity.h"


class Player : public QGraphicsEllipseItem, public DynamicEntity
{
public:
    Player(qreal x, qreal y);

    void keyPressEvent(QKeyEvent *event);

private:
    bool _jumpInProgress;
};

#endif // PLAYER_H
