#include "include/entity.h"


Entity::Entity(qreal x, qreal y) :
    _x(x),
    _y(y)
{

}

qreal Entity::getXPos() const
{
    return _x;
}

qreal Entity::getYPos() const
{
    return _y;
}

void Entity::setXPos(qreal x)
{
    _x = x;
}

void Entity::setYPos(qreal y)
{
    _y = y;
}
