#include "include/entity.h"


Entity::Entity(qreal x, qreal y, QColor color) :
    _x(x),
    _y(y),
    _color(color)
{

}

Entity::Entity(qreal x, qreal y) :
    Entity(x, y, Qt::gray)
{

}
QColor Entity::color() const
{
    return _color;
}

void Entity::setColor(QColor newColor)
{
    _color = newColor;
}

void Entity::drawAt(qreal x, qreal y)
{
    _x = x;
    _y = y;
    setPos(x, y);
}
