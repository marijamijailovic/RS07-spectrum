#include "include/soundplayer.h"


QMediaPlayer* SoundPlayer::_musicPlayer = new QMediaPlayer();


SoundPlayer::SoundPlayer()
{

}

void SoundPlayer::playFile(const QString &path)
{
    _musicPlayer->setMedia(QUrl::fromLocalFile(path));
    _musicPlayer->play();
}
