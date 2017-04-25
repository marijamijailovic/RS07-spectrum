#ifndef LEVEL_H
#define LEVEL_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <vector>
#include "include/dynamicentity.h"
#include "include/block.h"
#include "include/cube.h"
#include "include/player.h"


class Level {
public:
    Level(Player *player);
    ~Level();

    // TODO delete operator= and copy-constructor

    void load(QGraphicsScene *scene) const;
    std::vector<Entity *> getStaticEntities() const;
    std::vector<DynamicEntity *> getDynamicEntities() const;

    void applyGravity(qreal g);

private:
    std::vector<Entity *> _staticEntities;          // TODO can be const T*?
    std::vector<DynamicEntity *> _dynamicEntities;
    Player *_player;
};

#endif // LEVEL_H
