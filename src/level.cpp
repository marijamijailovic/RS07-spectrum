#include "include/level.h"
#include <QMessageBox>
#include <QFile>
#include <QCoreApplication>


Level::Level(const QString &fileName, Player *player) :
    _player(player)
{
        // Determine which object to create
        switch (entityType) {
        case 's':   // Static
            addStaticEntity(lineStream);
            break;
        case 'd':   // Dynamic
            addDynamicEntity(lineStream);
            break;
        case 'p':   // Player
            int x, y;
            lineStream >> x >> y;
            _player->drawAt(x, y);
            break;
        default:
            break;
        }
    }
}

void Level::addStaticEntity(QTextStream &lineStream)
{
    int x, y, w, h;
    QString entityClass;
    lineStream >> entityClass >> x >> y >> w >> h;

    if (entityClass == "block")
        _staticEntities.push_back(new Block(x, y, w, h));
    // TODO Add here other static object types
}

void Level::addDynamicEntity(QTextStream &lineStream)
{
    int x, y, w, h;
    QString entityClass;
    lineStream >> entityClass >> x >> y >> w >> h;

    if (entityClass == "cube")
        _dynamicEntities.push_back(new Cube(x, y, w, h));
    // TODO Add here other dynamic object types
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
