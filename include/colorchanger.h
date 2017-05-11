#ifndef COLORCHANGER_H
#define COLORCHANGER_H

#include <QObject>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include "include/entity.h"
#include "include/colors.h"


class ColorChanger : public QObject, public Entity
{
    Q_OBJECT

public:
    ColorChanger(QGraphicsView *view, qreal x, qreal y, QColor color);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private slots:
    void expand();

private:
    qreal _x;
    qreal _y;
    qreal _r;
    QGraphicsView *_view;
    QColor _color;
    QScopedPointer<QTimer> _expandTicker;
};

#endif // COLORCHANGER_H
