#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>


class Player : public QGraphicsEllipseItem
{
public:
    Player(int x, int y);

    void keyPressEvent(QKeyEvent *event);
};

#endif // PLAYER_H
