#ifndef ENTITY_H
#define ENTITY_H

#include <QtGlobal>
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include "include/colors.h"


class Entity : public QGraphicsObject
{
    Q_OBJECT

public:
    Entity(qreal x, qreal y, const QColor color = SpectrumColors::gray, bool collidable = true);

    void setPosition(qreal x, qreal y);
    qreal x() const;
    qreal y() const;
    QColor color() const;
    void setColor(const QColor newColor);
    bool collidable() const;

    virtual qreal centerX() const;
    virtual qreal centerY() const;

protected:
    qreal _x;
    qreal _y;
    QColor _color;
    bool _collidable;
};

#endif // ENTITY_H
