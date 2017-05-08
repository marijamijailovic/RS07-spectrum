#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScopedPointer>
#include <QTimer>
#include "include/player.h"
#include "include/background.h"
#include "include/level.h"
#include "include/colors.h"
#include "include/colorchanger.h"


class SpectrumGame : public QGraphicsScene
{
    Q_OBJECT

public:
    SpectrumGame(QGraphicsView *parent);
    ~SpectrumGame();

    SpectrumGame(const SpectrumGame&) = delete;
    SpectrumGame& operator=(const SpectrumGame&) = delete;

    void loadLevel(const QString id);

    void pause();
    void resume();

    QColor activeColor() const;
    void setActiveColor(QColor newActiveColor);

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void update() const;

private:
    void changeActiveColor(QKeyEvent *event);
    void animateColorChange();
    void stopColorChangeAnimation();

    QGraphicsView *_parent;
    qreal _gravCoeff = 1;
    QScopedPointer<Player> _player;
    QScopedPointer<Background> _background;
    QScopedPointer<Level> _level;
    QScopedPointer<QTimer> _gameTicker;
    QColor _activeColor = SpectrumColors::defaultActiveColor;
    QScopedPointer<ColorChanger> _colorCircle;
    QScopedPointer<QTimer> _colorCircleTicker;
};

#endif // GAME_H
