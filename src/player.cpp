#include "include/player.h"
#include <QBrush>
#include <QPixmap>
#include <QTextStream>

Player::Player(qreal x, qreal y) :
    DynamicEntity::DynamicEntity(x, y, 1)
{
    setZValue(1);
}

void Player::setJump(bool b)
{
    _jump = b;
}

void Player::setLeft(bool b)
{
    _left = b;
}

void Player::setRight(bool b)
{
    _right = b;
}

void Player::setUp(bool b)
{
    _up = b;
}

void Player::setDown(bool b)
{
    _down = b;
}

QRectF Player::boundingRect() const
{
    return QRectF(_x, _y, _w, _h);
}

QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addRect(_x, _y, _w, _h);
    return path;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(_x, _y, _w, _h, QPixmap(":sprites/player.png"));
}

qreal Player::centerX() const
{
    return _x + _w/2;
}

qreal Player::centerY() const
{
    return _y + _h/2;
}

void Player::move()
{
    QTextStream out(stdout);
    QList<QGraphicsItem *> collidingObjects = collidingItems();
    int ignoredCollisions = 0;
    bool onLadder = false;
    foreach (QGraphicsItem *item, collidingObjects) {
        if ( !((Entity*)item)->collidable()) {
            ignoredCollisions++;
            //out << "no collision\n";
            continue;
        }
        // If the item is a key, collect it and unlock the binded door
        if (typeid(*item) == typeid(Key)) {
            ((Key*)item)->unlockDoor();
            // Redraw the door
            ((Key*)item)->door()->update();
            // Hide key from the scene
            // TODO: delete Key item from the scene (maybe ?)
            item->hide();
            ignoredCollisions++;
            continue;
        }

        // TEST, REMOVE
        if (typeid(*item) == typeid(ColorUnlocker)) {
            ((ColorUnlocker*)item)->collect();
            ignoredCollisions++;
            continue;
        }
        // TEST, REMOVE

        QRectF a = mapToScene(boundingRect()).boundingRect();
        QRectF b = item->boundingRect();

        if (typeid(*item) == typeid(Ladder)) {
            int step = 4;
            //out << "ladder\n";
            // Player is not on the ladder if it's just on the top of it
            if (a.bottom() >= b.top() + 1 && a.bottom() < b.bottom())
                onLadder = true;
            if (_up && a.bottom() >= b.top() + step - 1)
                _y -= step;
            if (_down && a.bottom() <= b.bottom())
                _y += step;
            continue;
        }

        // Collisions
        if (_vy >= 0 && a.bottom() > b.top() && _vy >= a.bottom() - b.top()) {
            _y += b.top() - a.bottom() + 0.9145;
            _canJump = 2;
            //out << "bottom";
        } else if(_vy <= 0 && a.top() < b.bottom() && 1 - _vy >= b.bottom() - a.top()) {
            _y += b.bottom() - a.top() + 0.9145;
            _vy = 0;
            _canJump = -1;
            _inAir = true;
            //out << "bottom";
        } else if(_vx != 0 && a.right() > b.left() && a.right() - b.left() < _vx + 1) {
            _x += b.left() - a.right() - 1;
            _vx = 0;
            //out << "right";
        } else if(_vx != 0 && a.left() < b.right() && b.right() - a.left() < -_vx + 1) {
            _x += b.right() - a.left() + 1;
            _vx = 0;
            //out << "left";
        }
    }

    // TODO II disable top collision if the player is onLadder
    //purpose of canJump is wall jumping, currently disabled
    if (collidingObjects.size() == ignoredCollisions) {
        _inAir = true;
        if(_canJump)
            _canJump--;
    } else if (_jump && _canJump > 0) {
        _jump = false;
        _inAir = true;
        _vy = -10;
    } else if (_canJump < 0) {
        if (!_inAir)
            _canJump = 0;
    } else {
        _inAir = false;
        _jump = false;
        if (_vy > 0 && _canJump)
            _vy = 0;
    }

    if (_canJump == 0)
        _jump = false;

    //applyForce(-_vx*0.03,0);    // Air resistance

    // If left/right key is pressed, move the player
    if (_left)
        _vx -= 1;
    if (_right)
        _vx += 1;

    // TODO get frictionCoef from an entity that is under the player (advanced and not necessary)
    qreal frictionCoef = 0.1;
    if (_inAir == false)
        applyForce(-_vx * frictionCoef, 0);

    //TODO reset _vx = 0 when it becomes insignificant

    //out << "vx: " << _vx << " , vy: " << _vy << "\n";

    _y += _vy;
    if (!(onLadder && collidingObjects.size() > 1))
        _x += _vx;

    setPosition(_x, _y);
}
