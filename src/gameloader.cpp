#include "include/gameloader.h"
#include <QMessageBox>


GameLoader::GameLoader(const QString &fileName) :
    _valid(true),
    _gameSaveFile(new QFile(fileName))
{
    if (_gameSaveFile->open(QIODevice::ReadOnly) == false) {
        QMessageBox::information(nullptr, "Error", "Loading game failed\nCreating new game...");
        _valid = false;
    }
    _fStream.reset(new QTextStream(_gameSaveFile.data()));
}

GameLoader::~GameLoader()
{
    _gameSaveFile->close();
}

bool GameLoader::isValid() const
{
    return _valid;
}

#include <QDebug>
QString GameLoader::writeGameData(bool unlockedColors[], std::vector<bool> &completedLevels)
{
    // Read level ID
    QString level = _fStream->readLine().trimmed();

    // Read unlocked color IDs
    QString line = _fStream->readLine().trimmed();
    QTextStream colorsLineStream(&line);
    while (!colorsLineStream.atEnd()) {
        int id;
        colorsLineStream >> id;
        unlockedColors[id] = true;
    }

    if (level.toUInt() >= completedLevels.size())
        completedLevels.resize(level.toInt() + 1, false);

    // Read completed level IDs
    line = _fStream->readLine().trimmed();
    QTextStream levelsLineStream(&line);
    while (!levelsLineStream.atEnd()) {
        int id;
        levelsLineStream >> id;
        completedLevels[id] = true;
    }

    return level;
}
