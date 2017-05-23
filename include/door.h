#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QTimer>
#include "include/colors.h"
#include "include/entity.h"


class Door : public Entity
{
    Q_OBJECT

public:
    Door(qreal x,
         qreal y,
         const QString& nextLevel,
         const QColor color = SpectrumColors::gray,
         bool locked = false);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void lock();
    void unlock();
    QString nextLevel() const;
    bool isLocked() const;
    bool changesDefaultSpawn() const;
    void setChangesDefaultSpawn(bool b);
    int spawnAtX() const;
    int spawnAtY() const;
    void setSpawnAtX(int x);
    void setSpawnAtY(int y);

private slots:
    void shrinkBars();

private:
    qreal _barH;
    bool _locked;
    bool _drawBars;
    QScopedPointer<QTimer> _barShrinkTicker;
    QString _nextLevel;
    bool _changesDefaultSpawn;
    int _spawnAtX = 200;
    int _spawnAtY = 200;
};

#endif // DOOR_H
