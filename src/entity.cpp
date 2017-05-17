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

void Entity::setPosition(qreal x, qreal y)
{
    _x = x;
    _y = y;
}

qreal Entity::x() const
{
    return _x;
}

qreal Entity::y() const
{
    return _y;
}

qreal Entity::centerX() const
{
    return _x;
}

qreal Entity::centerY() const
{
    return _y;
}

bool Entity::collidable() const
{
    return _collidable;
}
