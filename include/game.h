#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScopedPointer>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include "include/player.h"
#include "include/level.h"
#include "include/colors.h"
#include "include/colorchanger.h"
#include "include/colorchooser.h"

#include <QTextStream>


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
    bool isUnlocked(const QColor &color) const;
    bool isUnlocked(int colorID) const;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private slots:
    void update() const;
    void unlockColor(int id);
    void stopColorChangeAnimation();
    void keyCollected();

private:
    void connectSlots(std::vector<Entity*> entities);
    void changeActiveColor(QKeyEvent *event);
    void animateColorChange(QColor color);
    void hideObjectsWithActiveColor();
    void openSpectrum();
    void closeSpectrum();

    bool _paused;
    bool _expandInProgress;
    QGraphicsView *_parent;
    const qreal _gravCoeff = 0.25;
    QColor _activeColor;
    QColor _oldActiveColor;
    QScopedPointer<Player> _player;
    QScopedPointer<Level> _level;
    QScopedPointer<ColorChanger> _colorCircle;
    QScopedPointer<ColorChooser> _spectrum;
    QScopedPointer<QTimer> _gameTicker;
    QScopedPointer<QTimer> _colorCircleTicker;
    bool _unlockedColors[SpectrumColors::COLOR_NUM];
};

#endif // GAME_H
