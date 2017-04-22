#ifndef PLAYER_H
#define PLAYER_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include "include/dynamicentity.h"


class Player : public DynamicEntity, public QGraphicsEllipseItem
{
public:
    Player(qreal x, qreal y);

    void keyPressEvent(QKeyEvent *event);

    void drawAt(qreal x, qreal y);

private:
    bool _jumpInProgress;
};

#endif // PLAYER_H
