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
    Level(const QString &id, Player &player, QColor *activeColor);
    ~Level();

    Level(const Level&) = delete;
    Level& operator=(const Level&) = delete;

    void load(QGraphicsScene *scene) const;
    std::vector<Entity *> staticEntities() const;
    std::vector<DynamicEntity *> dynamicEntities() const;
    unsigned id() const;

    void applyGravity(qreal g);

    void removeStaticEntity(Entity *item);
    void removeDynamicEntity(DynamicEntity *item);

private:
    std::vector<Entity *> _staticEntities;
    std::vector<DynamicEntity *> _dynamicEntities;
    Player &_player;
    unsigned _id;
};

#endif // LEVEL_H
