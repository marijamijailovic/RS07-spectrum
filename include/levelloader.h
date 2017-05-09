#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <QTextStream>
#include <QColor>
#include <vector>
#include "include/entity.h"
#include "include/dynamicentity.h"
#include "include/block.h"
#include "include/wall.h"
#include "include/ladder.h"
#include "include/door.h"
#include "include/key.h"
#include "include/cube.h"
#include "include/player.h"
#include "include/colors.h"


class LevelLoader
{
public:
    LevelLoader(const QString &fileName);
    ~LevelLoader();

    LevelLoader(const LevelLoader&) = delete;
    LevelLoader& operator=(const LevelLoader&) = delete;

    void parse(Player &player,
               QColor *activeColor,
               std::vector<Entity *> &staticEntities,
               std::vector<DynamicEntity *> &dynamicEntities) const;

private:
    void addStaticEntity(std::vector<Entity *> &staticEntities,
                         QTextStream &lineStream,
                         const QColor &entityColor,
                         const QColor &activeColor) const;
    void addDynamicEntity(std::vector<DynamicEntity *> &dynamicEntities,
                          QTextStream &lineStream,
                          const QColor &entityColor,
                          const QColor &activeColor) const;
    QColor readColor(QTextStream &lineStream) const;

    QFile *_levelFile;
    QTextStream *_fStream;
};

#endif // LEVELLOADER_H
