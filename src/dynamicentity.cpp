#include "include/dynamicentity.h"

DynamicEntity::DynamicEntity(qreal x, qreal y, qreal mass) :
    Entity::Entity(x, y),
    _mass(mass)
{

}

void DynamicEntity::setX(qreal x)
{
    _x = x;
}

void DynamicEntity::setY(qreal y)
{
    _y = y;
}

void DynamicEntity::setMass(qreal m)
{
    _mass = m;
}

void DynamicEntity::applyGravity(qreal g)
{
    _y -= g;

    // TODO
    // Add mass to equation
}
