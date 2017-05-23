#include "include/level.h"


Level::Level(const QString &fileName, Player &player, QColor *activeColor) :
    _player(player)
{
    LevelLoader l(fileName);
    l.parse(_player, activeColor, _staticEntities, _dynamicEntities);
}

Level::~Level()
{
    for (unsigned i = 0; i < _staticEntities.size(); i++)
        delete _staticEntities[i];
    // Player shouldn't be deleted twice
    for (unsigned i = 1; i < _dynamicEntities.size(); i++)
        delete _dynamicEntities[i];
}

void Level::load(QGraphicsScene *scene) const
{
    for (unsigned i = 0; i < _staticEntities.size(); i++)
        scene->addItem(_staticEntities[i]);
    // Player is already added to the scene
    for (unsigned i = 1; i < _dynamicEntities.size(); i++)
        scene->addItem(_dynamicEntities[i]);
}

std::vector<Entity *> Level::staticEntities() const
{
    return _staticEntities;
}

std::vector<DynamicEntity *> Level::dynamicEntities() const
{
    return _dynamicEntities;
}

void Level::applyGravity(qreal g)
{
    for (unsigned i = 0; i < _dynamicEntities.size(); i++)
        _dynamicEntities[i]->applyGravity(g);
}
