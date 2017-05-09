#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QTimer>
#include "include/colors.h"
#include "include/entity.h"


class Door : public QObject, public Entity
{
    Q_OBJECT

public:
    Door(qreal x, qreal y, const QColor color = SpectrumColors::gray, bool locked = false);

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void lock();
    void unlock();

private slots:
    void shrinkBars();

private:
    const int _w = 60;
    const int _h = 100;
    qreal _barH;
    bool _locked;
    bool _drawBars;
    QScopedPointer<QTimer> _barShrinkTicker;
};

#endif // DOOR_H
