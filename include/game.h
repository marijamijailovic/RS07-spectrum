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

    SpectrumGame(const SpectrumGame&) = delete;
    SpectrumGame& operator=(const SpectrumGame&) = delete;

private slots:
    void update() const;

private:
    qreal _gravCoeff = 1;
    Player *_player;
    QGraphicsScene *_scene;
    Level *_level;
    QTimer *_gameTicker;
};

#endif // GAME_H
