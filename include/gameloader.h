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

    bool isValid() const;
    void writeGameData();

private:
    bool _valid;
    QScopedPointer<QFile> _gameSaveFile;
    QScopedPointer<QTextStream> _fStream;
};

#endif // GAMELOADER_H
