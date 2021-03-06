#ifndef ENTITY_H
#define ENTITY_H

#include <QtGlobal>
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QTextStream>
#include "include/colors.h"


class Entity : public QGraphicsObject
{
    Q_OBJECT

public:
    Entity(qreal x, qreal y, qreal w, qreal h,
           const QColor color = SpectrumColors::gray,
           bool collidable = true);

    // Overrides from QGraphicsObject
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;

    QColor color() const;
    void setColor(const QColor newColor);
    bool collidable() const;

    virtual qreal centerX() const;
    virtual qreal centerY() const;

protected:
    qreal _w;
    qreal _h;
    QColor _color;
    bool _collidable;
};

#endif // ENTITY_H
