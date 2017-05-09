#ifndef COLORCHANGER_H
#define COLORCHANGER_H

#include <QObject>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include "include/colors.h"


class ColorChanger : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    ColorChanger(QGraphicsView *view, qreal x, qreal y, QColor color);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private slots:
    void expand();

private:
    void run();

    qreal _x;
    qreal _y;
    qreal _r;
    QGraphicsView *_view;
    QColor _color;
    QScopedPointer<QTimer> _expandTicker;
};

#endif // COLORCHANGER_H
