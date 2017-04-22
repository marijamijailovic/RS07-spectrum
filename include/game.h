#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
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
    void applyGravity() const;

private:
    qreal _gravCoeff = 5;
    Player *_player;
    QGraphicsScene *_scene;
    Level *_level;
};

#endif // GAME_H
