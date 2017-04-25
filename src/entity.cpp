#include "include/entity.h"


Entity::Entity(qreal x, qreal y) :
    _x(x),
    _y(y)
{

}

void Entity::drawAt(qreal x, qreal y)
{
    _x = x;
    _y = y;
    setPos(x, y);
}
