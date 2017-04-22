#include "include/level.h"

Level::Level()
{
    // TODO
    // Static entities:     walls or whatever non-moving
    // Dynamic entities:    everything affected by gravity
    // Add new entities to arrays
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
}

void Level::applyGravity(qreal g)
{
    // TODO
    // For each dynamic entity, call it's applyGravity
}
