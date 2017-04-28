#ifndef LEVEL_H
#define LEVEL_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <vector>
#include "include/entity.h"
#include "include/dynamicentity.h"
#include "include/levelloader.h"


class Level {
public:
    Level(const QString &fileName, Player *player);
    ~Level();

    Level(const Level&) = delete;
    Level& operator=(const Level&) = delete;

    void load(QGraphicsScene *scene) const;
    std::vector<Entity *> StaticEntities() const;
    std::vector<DynamicEntity *> DynamicEntities() const;

    void applyGravity(qreal g);

private:
    std::vector<Entity *> _staticEntities;
    std::vector<DynamicEntity *> _dynamicEntities;
    Player *_player;
};

#endif // LEVEL_H
