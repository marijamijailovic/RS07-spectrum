#ifndef LEVEL_H
#define LEVEL_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <vector>
#include "include/entity.h"
#include "include/dynamicentity.h"


class Level {
public:
    Level();
    ~Level();

    // TODO delete operator= and copy-constructor

    void load(QGraphicsScene *scene);

private:
    void applyGravity(qreal g);

    std::vector<Entity *> _staticEntities;          // TODO can be const?
    std::vector<DynamicEntity *> _dynamicEntities;
};

#endif // LEVEL_H
