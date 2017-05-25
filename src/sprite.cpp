#include "include/sprite.h"

Sprite::Sprite() :
    _current(0)
{
    _sprites.push_back(QPixmap(":sprites/0.png"));
    _sprites.push_back(QPixmap(":sprites/1.png"));
    _sprites.push_back(QPixmap(":sprites/2.png"));
    _sprites.push_back(QPixmap(":sprites/3.png"));
    _sprites.push_back(QPixmap(":sprites/4.png"));
    connect(&_ticker, SIGNAL(timeout()), this, SLOT(change()));
    _ticker.start(2000);
}

QPixmap Sprite::nextFrame() const
{
    return _sprites[_current];
}

void Sprite::change()
{
    if (_current == 0)
        _ticker.setInterval(90);

    if (_ind) {
        _current = (_current + 1) % 5;
        if (_current == 4)
            _ind = false;
    }
    else
        _current = (_current - 1) % 5;

    if (_current == 0) {
        _ind = true;
        _ticker.setInterval(5000);
    }
}
