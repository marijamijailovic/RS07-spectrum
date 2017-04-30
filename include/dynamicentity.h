#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include <QtGlobal>
#include <vector>
#include "include/entity.h"


class DynamicEntity : public Entity
{
public:
    DynamicEntity(qreal x, qreal y, qreal mass, const QColor color = Qt::gray, bool collidable = true);

    void applyForce(qreal ix, qreal iy);
    void applyGravity(qreal g);

    virtual void move() = 0;

protected:
    bool _inAir;
    qreal _mass;
    qreal _vx;
    qreal _vy;
};

#endif // DYNAMICENTITY_H
