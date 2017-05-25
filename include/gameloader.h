#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <QFile>
#include <QScopedPointer>
#include <QTextStream>


class GameLoader
{
public:
    GameLoader(const QString &fileName, char flag);
    ~GameLoader();

    GameLoader(const GameLoader&) = delete;
    GameLoader& operator=(const GameLoader&) = delete;

    bool isValid() const;

    QString readGameData(bool unlockedColors[],
                          std::vector<bool> &completedLevels);
    void writeGameData(unsigned levelID,
                       const bool unlockedColors[],
                       const std::vector<bool> &completedLevels);

private:
    bool _valid;
    QScopedPointer<QFile> _gameSaveFile;
    QScopedPointer<QTextStream> _fStream;
};

#endif // GAMELOADER_H
