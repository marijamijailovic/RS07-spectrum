#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include <QtGlobal>
#include <vector>
#include "include/entity.h"


class DynamicEntity : public Entity
{
public:
    DynamicEntity(qreal x, qreal y, qreal mass, QColor color = Qt::gray);

    void applyForce(qreal ix, qreal iy);

    virtual void move() =0 ;

protected:
    bool _inAir;
    qreal _mass;
    qreal _vx;
    qreal _vy;
};

#endif // DYNAMICENTITY_H
