#ifndef LASER_H
#define LASER_H

#include <QScopedPointer>
#include <QTimer>
#include "include/entity.h"


class Laser : public Entity
{
    Q_OBJECT

public:
    Laser(qreal x, qreal y,
          qreal dx = 0,
          const QColor color = SpectrumColors::black);

    // Overrides from Entity
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private slots:
    void move();

private:
    qreal calculateLaserLength() const;

    qreal _step;
    qreal _laserPos;
    QScopedPointer<QTimer> _moveTicker;
};

#endif // LASER_H
