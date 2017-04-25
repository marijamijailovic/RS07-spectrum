#include "include/level.h"

Level::Level()
{
    // TODO
    // Static entities:     walls or whatever non-moving
    // Dynamic entities:    everything affected by gravity
    // Add new entities to arrays
    _staticEntities.push_back(new Block(0, 300, 50, 50));
    _staticEntities.push_back(new Block(50, 280, 100, 50, Qt::blue));
    _staticEntities.push_back(new Block(150, 250, 100, 100, Qt::red));
    _staticEntities.push_back(new Block(250, 210, 50, 50, Qt::green));
    _staticEntities.push_back(new Block(300, 240, 100, 50, Qt::yellow));
    _staticEntities.push_back(new Block(400, 280, 100, 50, Qt::blue));
    _staticEntities.push_back(new Block(500, 300, 200, 50));
    _staticEntities.push_back(new Block(0, 360, 700, 50));

    //_dynamicEntities.push_back(new Cube(20, 20, 50, 50));
}

Level::~Level()
{
    // TODO
    // Free entity arrays
}

void Level::load(QGraphicsScene *scene) const
{
    for (unsigned i = 0; i < _staticEntities.size(); i++)
        scene->addItem(_staticEntities[i]);
    for (unsigned i = 0; i < _dynamicEntities.size(); i++)
        scene->addItem(_dynamicEntities[i]);
}

std::vector<Entity *> Level::getStaticEntities() const
{
    return _staticEntities;
}

std::vector<DynamicEntity *> Level::getDynamicEntities() const
{
    return _dynamicEntities;
}

void Level::applyGravity(qreal g)
{
    for (unsigned i = 0; i < _dynamicEntities.size(); i++)
        _dynamicEntities[i]->applyForce(0,g);
}
/*void Level::move(qreal g)
{
    for (unsigned i = 0; i < _dynamicEntities.size(); i++)
        _dynamicEntities[i]->move();
}*/
