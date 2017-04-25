#include "include/dynamicentity.h"
#include <QTextStream>

DynamicEntity::DynamicEntity(qreal x, qreal y, qreal mass, QColor color) :
    Entity::Entity(x, y),
    _inAir(true),
    _mass(mass),
    _vx(0),
    _vy(0)
{
    setColor(color);
}

// TODO

void DynamicEntity::applyForce(qreal ix,qreal iy)
{
    //QTextStream out(stdout);
    //out <<_x<< " : "<<_y;
    _vx+=ix;
    _vy+=iy;
}
