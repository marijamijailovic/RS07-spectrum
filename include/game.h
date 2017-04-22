#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include "include/player.h"
#include "include/level.h"


class SpectrumGame {
public:
    SpectrumGame(QGraphicsScene *scene);
    ~SpectrumGame();

    // TODO delete operator= and copy-constructor

private:
    // TODO add timer for gravity, inside call Entity->apply and Level->apply

    Player *_player;
    QGraphicsScene *_scene;
    Level *_level;
};

#endif // GAME_H
