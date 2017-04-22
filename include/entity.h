#ifndef ENTITY_H
#define ENTITY_H

#include <QtGlobal>


class Entity
{
public:
    Entity(qreal x, qreal y);

    qreal getXPos() const;
    qreal getYPos() const;
    void setXPos(qreal x);
    void setYPos(qreal y);

    virtual void drawAt(qreal x, qreal y) = 0;

protected:
    qreal _x;
    qreal _y;
    // Color _color;
};

#endif // ENTITY_H
