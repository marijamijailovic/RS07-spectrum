#ifndef ENTITY_H
#define ENTITY_H

#include <QtGlobal>


class Entity {
public:
    Entity(qreal x, qreal y);

protected:
    qreal _x;
    qreal _y;
    // Color _color;
};

#endif // ENTITY_H
