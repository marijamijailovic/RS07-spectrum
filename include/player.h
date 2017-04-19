#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Player
{
public:
    Player(QGraphicsScene *scene, int x, int y);
    ~Player();

private:
    QGraphicsRectItem *_player;
    QGraphicsScene *_scene;
};

#endif // PLAYER_H
