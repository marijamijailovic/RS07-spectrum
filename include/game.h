#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "include/player.h"
#include "include/level.h"
#include "colors.h"


class SpectrumGame : public QGraphicsScene
{
    Q_OBJECT

public:
    SpectrumGame();
    ~SpectrumGame();

    SpectrumGame(const SpectrumGame&) = delete;
    SpectrumGame& operator=(const SpectrumGame&) = delete;

    QColor activeColor() const;
    void setActiveColor(QColor newActiveColor);

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void update() const;

private:
    void changeActiveColor(QKeyEvent *event);

    qreal _gravCoeff = 1;
    Player *_player;
    Level *_level;
    QTimer *_gameTicker;
    QColor _activeColor = SpectrumColors::blue;
};

#endif // GAME_H
