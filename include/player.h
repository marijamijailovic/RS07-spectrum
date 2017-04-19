#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>


class Player : public QGraphicsEllipseItem
{
public:
    Player(int x, int y);

    void ProcessKeyPress(int step);
};

#endif // PLAYER_H
