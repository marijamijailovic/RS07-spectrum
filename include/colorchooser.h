#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include <QTimer>
#include <QScopedPointer>
#include "include/entity.h"


class ColorChooser : public Entity
{
    Q_OBJECT

public:
    ColorChooser(qreal x, qreal y, const bool *unlockedColors);

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void relocate(qreal x, qreal y);

private:
    qreal _r;
    const bool *_unlockedColors;
};

#endif // COLORCHOOSER_H
