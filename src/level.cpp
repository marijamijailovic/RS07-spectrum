#include "include/level.h"
#include <QMessageBox>
#include <QFile>
#include <QCoreApplication>


Level::Level(const QString &fileName, Player *player) :
    _player(player)
{
    // Open level file
    QFile f(fileName);
    if (f.open(QIODevice::ReadOnly) == false) {
        QMessageBox::critical(nullptr, "Error",
            "Loading level failed\nLoading default level...");
        QFile fDef(":levels/001.lvl");
        if (fDef.open(QIODevice::ReadOnly) == false) {
            QMessageBox::critical(nullptr, "Error",
                "Loading level failed\nLoading default level...");
            QCoreApplication::exit(EXIT_FAILURE);
        }
    }

    // Parse level file
    QTextStream fStream(&f);
    parse(fStream);

    // Close level file
    f.close();
}

void Level::parse(QTextStream &fStream)
{
    QColor entityColor = Qt::gray;
    // Read level file line by line
    while (!fStream.atEnd()) {
        QString line = fStream.readLine().trimmed();

        // Comments are lines starting with "#"
        if (line.isEmpty() || line.startsWith("#"))
            continue;

        // Read data from the current line
        QTextStream lineStream(&line);
        char entityType;
        lineStream >> entityType;

        // Determine which object to create
        switch (entityType) {
        case 's':   // Static
            addStaticEntity(lineStream, entityColor);
            break;
        case 'd':   // Dynamic
            addDynamicEntity(lineStream, entityColor);
            break;
        case 'c':   // Color
            int r, g, b;
            lineStream >> r >> g >> b;
            entityColor = QColor(r, g, b);
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

void Level::addStaticEntity(QTextStream &lineStream, QColor &entityColor)
{
    int x, y, w, h;
    QString entityClass;
    lineStream >> entityClass >> x >> y >> w >> h;

    if (entityClass == "block")
        _staticEntities.push_back(new Block(x, y, w, h, entityColor));
    // TODO Add here other static object types
}

void Level::addDynamicEntity(QTextStream &lineStream, QColor &entityColor)
{
    int x, y, w, h;
    QString entityClass;
    lineStream >> entityClass >> x >> y >> w >> h;

    if (entityClass == "cube")
        _dynamicEntities.push_back(new Cube(x, y, w, entityColor));
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

std::vector<Entity *> Level::StaticEntities() const
{
    return _staticEntities;
}

std::vector<DynamicEntity *> Level::DynamicEntities() const
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
