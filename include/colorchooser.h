#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include <QTimer>
#include <QScopedPointer>
#include "include/entity.h"


class ColorChooser : public Entity
{
    Q_OBJECT

public:
    ColorChooser(qreal x, qreal y);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // COLORCHOOSER_H
