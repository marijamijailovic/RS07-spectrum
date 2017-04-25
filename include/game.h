#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "include/player.h"
#include "include/level.h"


class SpectrumGame : private QObject
{
    Q_OBJECT

public:
    SpectrumGame(QGraphicsScene *scene);
    ~SpectrumGame();

    // TODO delete operator= and copy-constructor

private slots:
    void update() const;

private:
    qreal _gravCoeff = 1;
    Player *_player;
    QGraphicsScene *_scene;
    Level *_level;
};

#endif // GAME_H
