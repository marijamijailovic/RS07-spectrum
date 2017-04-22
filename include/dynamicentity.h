#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include <QtGlobal>
#include "include/entity.h"


class DynamicEntity : public Entity
{
public:
    DynamicEntity(qreal x, qreal y, qreal mass);

    void setX(qreal x);
    void setY(qreal y);
    void setMass(qreal m);

private:
    void applyGravity(qreal g);

    qreal _mass;
};

#endif // DYNAMICENTITY_H
