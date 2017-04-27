#include "include/levelloader.h"

#include <QMessageBox>
#include <QFile>
#include <QCoreApplication>


LevelLoader::LevelLoader(const QString &fileName)
{
    _levelFile = new QFile(fileName);
    if (_levelFile->open(QIODevice::ReadOnly) == false) {
        QMessageBox::critical(nullptr, "Error",
            "Loading level failed\nLoading default level...");
        QFile fDef(":levels/001.lvl");
        if (fDef.open(QIODevice::ReadOnly) == false) {
            QMessageBox::critical(nullptr, "Error",
                "Loading level failed\nLoading default level...");
            QCoreApplication::exit(EXIT_FAILURE);
        }
    }
    _fStream = new QTextStream(_levelFile);
}

LevelLoader::~LevelLoader()
{
    // Close level file
    _levelFile->close();

    delete _levelFile;
    delete _fStream;
}

void LevelLoader::parse(Player *player, std::vector<Entity *> &staticEntities, std::vector<DynamicEntity *> &dynamicEntities) const
{
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
            addStaticEntity(staticEntities, lineStream, entityColor);
            break;
        case 'd':   // Dynamic
            addDynamicEntity(dynamicEntities, lineStream, entityColor);
            break;
        case 'c':   // Color
            entityColor = readColor(lineStream);
            break;
        case 'p':   // Player
            int x, y;
            lineStream >> x >> y;
            player->drawAt(x, y);
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

    if (colorName == "red") {
        return SpectrumColors::red;
    } else if (colorName == "green") {
        return SpectrumColors::green;
    } else if (colorName == "blue") {
        return SpectrumColors::blue;
    } else if (colorName == "yellow") {
        return SpectrumColors::yellow;
    } else if (colorName == "purple") {
        return SpectrumColors::purple;
    } else if (colorName == "orange") {
        return SpectrumColors::orange;
    } else if (colorName == "gray") {
        return SpectrumColors::gray;
    } else
        return SpectrumColors::pink;
}

void LevelLoader::addStaticEntity(std::vector<Entity *> &staticEntities, QTextStream &lineStream, QColor &entityColor) const
{
    int x, y, w, h;
    QString entityClass;
    lineStream >> entityClass >> x >> y >> w >> h;

    if (entityClass == "block")
        staticEntities.push_back(new Block(x, y, w, h));
    else if (entityClass == "wall")
        staticEntities.push_back(new Wall(x, y, w, h, entityColor));
    else if (entityClass == "ladder")
        staticEntities.push_back(new Ladder(x, y, w, h, entityColor));
    else if (entityClass == "key")
        staticEntities.push_back(new Key(x, y, entityColor));
    else if (entityClass == "door")
        staticEntities.push_back(new Door(x, y, entityColor));
    // TODO Add here other static object types
}

void LevelLoader::addDynamicEntity(std::vector<DynamicEntity *> &dynamicEntities, QTextStream &lineStream, QColor &entityColor) const
{
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
}