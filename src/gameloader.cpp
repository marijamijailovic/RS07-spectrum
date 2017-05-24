#include "include/gameloader.h"
#include <QMessageBox>


GameLoader::GameLoader(const QString &fileName) :
    _gameSaveFile(new QFile(fileName))
{
    if (_gameSaveFile->open(QIODevice::ReadOnly) == false)
        QMessageBox::critical(nullptr, "Error", "Loading game failed\n...");
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
