#ifndef COLORCHANGER_H
#define COLORCHANGER_H

#include <QObject>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include "include/entity.h"
#include "include/colors.h"


class ColorChanger : public Entity
{
    Q_OBJECT

public:
    ColorChanger(QGraphicsView *view, qreal x, qreal y, QColor color);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

signals:
    void expandingDone();

private slots:
    void expand();

private:
    QGraphicsView *_view;
    QScopedPointer<QTimer> _expandTicker;
};

#endif // COLORCHANGER_H
