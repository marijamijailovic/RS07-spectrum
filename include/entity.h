#ifndef ENTITY_H
#define ENTITY_H

#include <QtGlobal>
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>


class Entity : public QGraphicsItem
{
public:
    Entity(qreal x, qreal y);
    Entity(qreal x, qreal y, QColor color);

    void drawAt(qreal x, qreal y);
    QColor color() const;
    void setColor(QColor newColor);

protected:
    qreal _x;
    qreal _y;
    QColor _color;
};

#endif // ENTITY_H
