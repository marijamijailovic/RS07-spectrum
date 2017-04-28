#include "include/dynamicentity.h"
#include <QTextStream>

DynamicEntity::DynamicEntity(qreal x, qreal y, qreal mass, const QColor color) :
    Entity::Entity(x, y, color),
    _inAir(true),
    _mass(mass),
    _vx(0),
    _vy(0)
{

}

void DynamicEntity::applyForce(qreal ix,qreal iy)
{
    _vx += (ix / _mass);
    if (_vx > 10)
        _vx = 10;
    if (_vx < -10)
        _vx=-10;
    _vy += (iy / _mass);
}

void DynamicEntity::applyGravity(qreal g)
{
    applyForce(0, g);
}
