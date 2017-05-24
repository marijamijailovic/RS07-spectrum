#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QMediaPlayer>

class SoundPlayer
{
public:
    static void playFile(const QString &path);

private:
    SoundPlayer();

    static QMediaPlayer *_musicPlayer;
};

#endif // SOUNDPLAYER_H
