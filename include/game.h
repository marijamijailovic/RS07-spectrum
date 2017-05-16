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
#include "include/colorchooser.h"


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
    void interact();

    QColor activeColor() const;
    void setActiveColor(QColor newActiveColor);
    void unlockColor(int id);
    bool isUnlocked(const QColor &color) const;

    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private slots:
    void update() const;
    void stopColorChangeAnimation();

private:
    void changeActiveColor(QKeyEvent *event);
    void animateColorChange();
    void hideObjectsWithActiveColor();
    void openSpectrum();
    void closeSpectrum();

    bool _paused;
    bool _expandInProgress;
    QGraphicsView *_parent;
    qreal _gravCoeff = 1;
    QColor _activeColor;
    QScopedPointer<Player> _player;
    QScopedPointer<Background> _background;
    QScopedPointer<Level> _level;
    QScopedPointer<ColorChanger> _colorCircle;
    QScopedPointer<ColorChooser> _spectrum;
    QScopedPointer<QTimer> _gameTicker;
    QScopedPointer<QTimer> _colorCircleTicker;
    bool _unlockedColors[SpectrumColors::COLOR_NUM];
};

#endif // GAME_H
