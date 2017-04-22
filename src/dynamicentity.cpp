#include "include/dynamicentity.h"

DynamicEntity::DynamicEntity(qreal x, qreal y, qreal mass) :
    Entity::Entity(x, y),
    _mass(mass),
    _vx(0),
    _vy(0)
{

}

qreal DynamicEntity::getMass() const
{
    return _mass;
}

qreal DynamicEntity::getVelX() const
{
    return _vx;
}

qreal DynamicEntity::getVelY() const
{
    return _vy;
}

void DynamicEntity::setMass(qreal m)
{
    _mass = m;
}

void DynamicEntity::setVelX(qreal v)
{
    _vx = v;
}

void DynamicEntity::setVelY(qreal v)
{
    _vy = v;
}

void DynamicEntity::applyGravity(qreal g)
{
    _y = _y + _mass + g;
    drawAt(_x, _y);
}
