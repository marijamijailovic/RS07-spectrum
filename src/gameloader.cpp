#include "include/gameloader.h"
#include <QMessageBox>


GameLoader::GameLoader(const QString &fileName) :
    _valid(true),
    _gameSaveFile(new QFile(fileName))
{
    if (_gameSaveFile->open(QIODevice::ReadOnly) == false) {
        QMessageBox::critical(nullptr, "Error", "Loading game failed\nCreating new game...");
        _valid = false;
    }
    _fStream.reset(new QTextStream(_gameSaveFile.data()));
}

#include <QDebug>
void GameLoader::writeGameData()
{
    while (!_fStream->atEnd()) {
        QString line = _fStream->readLine().trimmed();
        qDebug() << line;
    }
}

GameLoader::~GameLoader()
{
    _gameSaveFile->close();
}

bool GameLoader::isValid() const
{
    return _valid;
}
