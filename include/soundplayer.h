#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QScopedPointer>
#include <QMediaPlayer>


class SoundPlayer : public QMediaPlayer
{
public:
    static void playFile(const QString &path);

private:
    SoundPlayer();
    static QScopedPointer<QMediaPlayer> _player;
};

#endif // SOUNDPLAYER_H
