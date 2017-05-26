#include "include/sprite.h"

Sprite::Sprite() :
    _current(0),
    _animationActive(false),
    _ind(true)
{
    connect(&_ticker, SIGNAL(timeout()), this, SLOT(change()));
    _ticker.start(2000);
}

bool Sprite::animationActive() const
{
    return _animationActive;
}

QPixmap Sprite::nextFrame() const
{
    return _sprites[_current];
}

void Sprite::addFrame(const QString& frame)
{
    _sprites.push_back(QPixmap(frame));
}

void Sprite::change()
{
    if (_current == 0) {
        _animationActive = true;
        _ticker.setInterval(90);
    }

    if (_ind) {
        _current = (_current + 1) % _sprites.size();
        if (_current == _sprites.size() - 1)
            _ind = false;
    }
    else
        _current = (_current - 1) % _sprites.size();

    if (_current == 0) {
        _ind = true;
        _animationActive = false;
        _ticker.setInterval(5000);
    }
}
