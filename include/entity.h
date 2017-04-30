#ifndef ENTITY_H
#define ENTITY_H

#include <QtGlobal>
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include "include/colors.h"


class Entity : public QGraphicsItem
{
public:
    Entity(qreal x, qreal y, const QColor color = SpectrumColors::gray, bool collidable = true);

    void drawAt(qreal x, qreal y);
    QColor color() const;
    void setColor(const QColor newColor);

    bool collidable() const;

protected:
    qreal _x;
    qreal _y;
    QColor _color;
    bool _collidable;
};

#endif // ENTITY_H
