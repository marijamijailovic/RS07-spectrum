#ifndef LEVEL_H
#define LEVEL_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <QTextStream>
#include <vector>
#include "include/dynamicentity.h"
#include "include/block.h"
#include "include/cube.h"
#include "include/player.h"


class Level {
public:
    Level(const QString &fileName, Player *player);
    ~Level();

    // TODO delete operator= and copy-constructor

    void load(QGraphicsScene *scene) const;
    std::vector<Entity *> StaticEntities() const;
    std::vector<DynamicEntity *> DynamicEntities() const;

    void applyGravity(qreal g);

private:
    void parse(QTextStream &fStream);
    void addStaticEntity(QTextStream &lineStream, QColor &entityColor);
    void addDynamicEntity(QTextStream &lineStream, QColor &entityColor);

    std::vector<Entity *> _staticEntities;          // TODO can be const T*?
    std::vector<DynamicEntity *> _dynamicEntities;
    Player *_player;
};

#endif // LEVEL_H
