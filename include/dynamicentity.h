#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include <QtGlobal>
#include <vector>
#include "include/entity.h"

class DynamicEntity : public Entity
{
public:
    DynamicEntity(qreal x, qreal y, qreal w, qreal h,
                  qreal mass,
                  const QColor color = SpectrumColors::gray,
                  bool collidable = true);

    void setVx(qreal vx);
    void setVy(qreal vy);
    void setCh(double c);
    double getCh() const;

    void applyForce(qreal ix, qreal iy);
    void applyGravity(qreal g);

    void move(int id);

protected:
    bool _inAir;
    qreal _mass;
    qreal _vx;
    qreal _vy;
    double _ch;
};

#endif // DYNAMICENTITY_H
