#include "include/dynamicentity.h"
#include <QTextStream>

DynamicEntity::DynamicEntity(qreal x, qreal y, qreal mass, const QColor color, bool collidable) :
    Entity::Entity(x, y, color, collidable),
    _inAir(true),
    _mass(mass),
    _vx(0),
    _vy(0),
    _ch(0)
{

}

void DynamicEntity::setVx(qreal vx)
{
    _vx = vx;
}

void DynamicEntity::setVy(qreal vy)
{
    _vy = vy;
}

void DynamicEntity::setCh(int c)
{
    _ch = c;
}

int DynamicEntity::getCh() const
{
    return _ch;
}

void DynamicEntity::applyForce(qreal ix, qreal iy)
{
    _vx += (ix / _mass);
    if (_vx > 3)
        _vx = 3;
    if (_vx < -3)
        _vx =- 3;
    _vy += (iy / _mass);
}

void DynamicEntity::applyGravity(qreal g)
{
    applyForce(0, g);
}
