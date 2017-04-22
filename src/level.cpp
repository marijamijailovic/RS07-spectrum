#include "include/level.h"

Level::Level()
{
    // TODO
    // Static entities:     walls or whatever non-moving
    // Dynamic entities:    everything affected by gravity
    // Add new entities to arrays

    _staticEntities.push_back(new Block(-250, 300, 500, 50));   // FIXME temp
}

Level::~Level()
{
    // TODO
    // Free entity arrays
}

void Level::load(QGraphicsScene *scene)
{
    // TODO
    // Add all entities to scene

    scene->addItem(_staticEntities[0]);     // FIXME temp
}

std::vector<Block *> Level::getStaticEntities() const
{
    return _staticEntities;
}

std::vector<DynamicEntity *> Level::getDynamicEntities() const
{
    return _dynamicEntities;
}

void Level::applyGravity(qreal g)
{
    // TODO
    // For each dynamic entity, call it's applyGravity
}
