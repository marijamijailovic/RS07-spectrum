#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include <QtGlobal>
#include <vector>
#include "include/entity.h"


class DynamicEntity : public Entity
{
public:
    DynamicEntity(qreal x, qreal y, qreal mass);

    qreal getMass() const;
    qreal getVelX() const;
    qreal getVelY() const;
    void setMass(qreal m);
    void setVelX(qreal v);
    void setVelY(qreal v);
    void applyGravity(qreal g);

private:
    qreal _mass;
    qreal _vx;
    qreal _vy;
};

#endif // DYNAMICENTITY_H
