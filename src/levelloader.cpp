#include "include/levelloader.h"
#include <QMessageBox>
#include <QFile>
#include <QCoreApplication>


LevelLoader::LevelLoader(const QString &fileName) :
    _levelFile(new QFile(fileName))
{
    if (_levelFile->open(QIODevice::ReadOnly) == false) {
        QMessageBox::information(nullptr, "Error", "Loading level failed\nLoading default level...");
        _levelFile.reset(new QFile(":levels/001.lvl"));
        _levelFile->open(QIODevice::ReadOnly);
    }
    _fStream.reset(new QTextStream(_levelFile.data()));
}

LevelLoader::~LevelLoader()
{
    // Close level file
    _levelFile->close();
}

void LevelLoader::parse(Player &player,
                        QColor *activeColor,
                        std::vector<Entity *> &staticEntities,
                        std::vector<DynamicEntity *> &dynamicEntities) const
{
    QString colorLine = _fStream->readLine().trimmed();
    // If colorLine is not specified, then it shouldn't be changed
    if (colorLine != "N/A") {
        *activeColor = SpectrumColors::getColorFromName(colorLine);
    }

    QColor entityColor = SpectrumColors::gray;
    // Read level file line by line
    while (!_fStream->atEnd()) {
        QString line = _fStream->readLine().trimmed();

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
            addStaticEntity(staticEntities, lineStream, entityColor, *activeColor);
            break;
        case 'd':   // Dynamic
            addDynamicEntity(dynamicEntities, lineStream, entityColor, *activeColor);
            break;
        case 'c':   // Color
            entityColor = readColor(lineStream);
            break;
        case 'p':   // Player
            int x, y;
            lineStream >> x >> y;
            dynamicEntities.push_back(&player);
            player.setPos(x, y);
            break;
        default:
            break;
        }
    }
}

QColor LevelLoader::readColor(QTextStream &lineStream) const
{
    QString colorName;
    lineStream >> colorName;
    return SpectrumColors::getColorFromName(colorName);
}

void LevelLoader::addStaticEntity(std::vector<Entity *> &staticEntities,
                                  QTextStream &lineStream,
                                  const QColor &entityColor,
                                  const QColor &activeColor) const
{
    int x, y, w, h;
    QString entityClass;
    lineStream >> entityClass >> x >> y;

    if (entityClass == "block") {
        lineStream >> w >> h;
        staticEntities.push_back(new Block(x, y, w, h));
    } else if (entityClass == "wall") {
        lineStream >> w >> h;
        staticEntities.push_back(new Wall(x, y, w, h, entityColor));
    } else if (entityClass == "ladder") {
        lineStream >> w >> h;
        staticEntities.push_back(new Ladder(x, y, w, h, entityColor));
    } else if (entityClass == "door") {
        QString nextLevel;
        lineStream >> nextLevel;
        Door *newDoor = new Door(x, y, nextLevel, entityColor);
        staticEntities.push_back(newDoor);
        if (! lineStream.atEnd()) {
            QString nextToken;
            lineStream >> nextToken;
            // Next Tokex could be: new player spawn coordinates or key
            // Also, after spawn could be key
            if (nextToken != "key") {
                int playerX, playerY;
                playerX = nextToken.toInt();
                lineStream >> playerY;
                newDoor->setSpawnAtX(playerX);
                newDoor->setSpawnAtY(playerY);
                newDoor->setChangesDefaultSpawn(true);
            } else {
                lineStream >> x >> y;
                staticEntities.push_back(new Key(x, y, newDoor, entityColor));
                newDoor->lock();
            }
            // If there is only a key next, bind the door and the key
            if (! lineStream.atEnd() ) {
                lineStream >> entityClass >> x >> y;
                staticEntities.push_back(new Key(x, y, newDoor, entityColor));
                newDoor->lock();
            }

        }
    } else if (entityClass == "unlocker") {
        staticEntities.push_back(new ColorUnlocker(x, y, entityColor));
    }

    if (activeColor == entityColor)
        staticEntities.back()->hide();
}

void LevelLoader::addDynamicEntity(std::vector<DynamicEntity *> &dynamicEntities,
                                   QTextStream &lineStream,
                                   const QColor &entityColor,
                                   const QColor &activeColor) const
{
    QTextStream out(stdout);
    int x, y, w, h;
    QString entityClass;
    lineStream >> entityClass;

    if (entityClass == "cube") {
        lineStream >> x >> y >> w;
        dynamicEntities.push_back(new Cube(x, y, w, entityColor));
    } else {
        lineStream >> x >> y >> w >> h;

        // TODO Add here other dynamic object types
    }
    if (entityClass == "cube"&&activeColor == entityColor)
        dynamicEntities.back()->hide();
}
