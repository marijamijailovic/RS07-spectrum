#include "include/sprite.h"

Sprite::Sprite() :
    _current(0),
    _inLoop(false),
    _ind(true)
{
    connect(&_ticker, SIGNAL(timeout()), this, SLOT(change()));
    _ticker.setInterval(90);
}

void Sprite::startAnimation()
{
    _ticker.start();
}

bool Sprite::animationActive() const
{
    return _ticker.isActive();
}

bool Sprite::inLoop() const
{
    return _inLoop;
}

void Sprite::setLoop(bool b)
{
    _inLoop = b;
}

int Sprite::tickerInterval() const
{
    return _ticker.interval();
}

void Sprite::setTickerInterval(int ms)
{
    _ticker.setInterval(ms);
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
    if (_current == 0 && !animationActive()) {
        _ticker.start();
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
        if (!_inLoop)
            _ticker.stop();
    }
}
