#ifndef GAME_H
#define GAME_H

#include "include/player.h"
#include <QGraphicsScene>

class SpectrumGame {
public:
    SpectrumGame(QGraphicsScene *scene);
    ~SpectrumGame();

private:
    Player *_player;
    QGraphicsScene *_scene;
};

#endif // GAME_H
