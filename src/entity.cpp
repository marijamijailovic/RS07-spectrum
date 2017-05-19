#include "include/entity.h"

Entity::Entity(qreal x, qreal y, const QColor color, bool collidable) :
    _color(color),
    _collidable(collidable)
{
    setPos(x, y);
}

QColor Entity::color() const
{
    return _color;
}

void Entity::setColor(const QColor newColor)
{
    _color = newColor;
}

qreal Entity::centerX() const
{
    return x();
}

qreal Entity::centerY() const
{
    return y();
}

bool Entity::collidable() const
{
    return _collidable;
}
