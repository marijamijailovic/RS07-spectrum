#ifndef LEVEL_H
#define LEVEL_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <vector>
#include "include/entity.h"
#include "include/dynamicentity.h"
#include "block.h"


class Level {
public:
    Level();
    ~Level();

    // TODO delete operator= and copy-constructor

    void load(QGraphicsScene *scene);
    std::vector<Block *> getStaticEntities() const;
    std::vector<DynamicEntity *> getDynamicEntities() const;

    void applyGravity(qreal g);

private:
    std::vector<Block *> _staticEntities;          // TODO can be const T*?
    std::vector<DynamicEntity *> _dynamicEntities;
};

#endif // LEVEL_H
