#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScopedPointer>
#include <QTimer>
#include "include/player.h"
#include "include/level.h"
#include "include/colors.h"


class SpectrumGame : public QGraphicsScene
{
    Q_OBJECT

public:
    SpectrumGame(QGraphicsView *parent);
    ~SpectrumGame();

    SpectrumGame(const SpectrumGame&) = delete;
    SpectrumGame& operator=(const SpectrumGame&) = delete;

    void pause();
    void resume();

    QColor activeColor() const;
    void setActiveColor(QColor newActiveColor);

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void update() const;

private:
    void changeActiveColor(QKeyEvent *event);

    QGraphicsView *_parent;
    qreal _gravCoeff = 1;
    QScopedPointer<Player> _player;
    QScopedPointer<Level> _level;
    QTimer *_gameTicker;
    QColor _activeColor = SpectrumColors::defaultActiveColor;
};

#endif // GAME_H
