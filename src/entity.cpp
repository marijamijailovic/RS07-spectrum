#include "include/entity.h"

Entity::Entity(qreal x, qreal y, const QColor color, bool collidable) :
    _x(x),
    _y(y),
    _color(color),
    _collidable(collidable)
{

}

QColor Entity::color() const
{
    return _color;
}

void Entity::setColor(const QColor newColor)
{
    _color = newColor;
}

void Entity::drawAt(qreal x, qreal y)
{
    _x = x;
    _y = y;
    setPos(x, y);
}

bool Entity::collidable() const
{
    return _collidable;
}
