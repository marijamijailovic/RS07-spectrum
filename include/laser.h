#ifndef LASER_H
#define LASER_H

#include <QScopedPointer>
#include <QTimer>
#include "include/entity.h"


class Laser : public Entity
{
    Q_OBJECT

public:
    enum Direction { UP, DOWN, LEFT, RIGHT };

    Laser(qreal x, qreal y,
          qreal dx = 0, qreal dy = 0,
          Direction direction = DOWN,
          const QColor color = SpectrumColors::black);

    // Overrides from Entity
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void hide() override;
    void show() override;

signals:
    void playerHit();

private slots:
    void move();

private:
    qreal calculateLaserLength();

    const qreal MAX_LASER_LEN = 800;
    const qreal LASER_WIDTH = 5;
    Direction _direction;
    bool _hidden;
    qreal _step;
    qreal _laserPos;
    QScopedPointer<QTimer> _moveTicker;
};

#endif // LASER_H
