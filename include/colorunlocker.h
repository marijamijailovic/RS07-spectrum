#ifndef COLORUNLOCKER_H
#define COLORUNLOCKER_H

#include <QObject>
#include <QTimer>
#include "include/entity.h"


class ColorUnlocker : public QObject, public Entity
{
    Q_OBJECT

public:
    ColorUnlocker(qreal x, qreal y, const QColor color);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void collect();

private slots:
    void incrementOpacity();
    void raise();

private:
    const qreal _w = 60;
    const qreal _h = 30;
    int _opacity;
    int _step;
    qreal _raiseH;
    QScopedPointer<QTimer> _opacityTicker;
    QScopedPointer<QTimer> _raiseTicker;
};

#endif // COLORUNLOCKER_H
