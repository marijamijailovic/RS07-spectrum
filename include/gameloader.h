#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <QFile>
#include <QScopedPointer>
#include <QTextStream>


class GameLoader
{
public:
    GameLoader(const QString &fileName);
    ~GameLoader();

    GameLoader(const GameLoader&) = delete;
    GameLoader& operator=(const GameLoader&) = delete;

    void writeGameData();

private:
    QScopedPointer<QFile> _gameSaveFile;
    QScopedPointer<QTextStream> _fStream;
};

#endif // GAMELOADER_H
