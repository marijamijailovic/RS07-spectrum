#include "include/player.h"
#include <QBrush>
#include <QPixmap>
#include <QTextStream>

Player::Player(qreal x, qreal y) :
    DynamicEntity::DynamicEntity(x, y, 60, 77, 1)
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
void Player::setPull(bool b)
{
    pull=b;
}
bool Player::getPull()
{
    return pull;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, _w, _h, QPixmap(":sprites/player.png"));
}

qreal Player::centerX() const
{
    return x() + _w/2;
}

qreal Player::centerY() const
{
    return y() + _h/2;
}
bool Player::go(){
    movement();
    int ignoredCollisions = 0;
    QList<QGraphicsItem *> collidingObjects = collidingItems();
    foreach (QGraphicsItem *item, collidingObjects) {
        if ( !((Entity*)item)->collidable()) {
            ignoredCollisions++;
            //out << "no collision\n";
            continue;
        }
    }
    if (collidingObjects.size() == ignoredCollisions){
        return true;
    }

    return false;
}
void Player::jump(){

    QTextStream out(stdout);
    if(_jump&&!_inAir) {
        _vy=-10;
        _jump=false;
    }
}

void Player::movement()
{
        QTextStream out(stdout);
    if (_left)
        applyForce(-1200,0);
    if (_right)
        applyForce(1200,0);
    double _x=0;
    double _y=0;
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
            ((Key*)item)->collect();
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
            out<<"ladder";
            ignoredCollisions++;
            /*int step = 4;
            //out << "ladder\n";
            // Player is not on the ladder if it's just on the top of it
            if (a.bottom() >= b.top() + 1 && a.bottom() < b.bottom())
                onLadder = true;
            if (_up && a.bottom() >= b.top() + step - 1)
                _y -= step;
            if (_down && a.bottom() <= b.bottom())
                _y += step;
            continue;*/
        }

    }
    // TODO II disable top collision if the player is onLadder
    //purpose of canJump is wall jumping, currently disabled

    //applyForce(-_vx*0.03,0);    // Air resistance

    // If left/right key is pressed, move the player
    /*if (_left)
        _vx -= 1;
    if (_right)
        _vx += 1;
*/
    // TODO get frictionCoef from an entity that is under the player (advanced and not necessary)
    qreal frictionCoef = 0.1;
    /*if (_inAir == false)
        applyForce(-_vx * frictionCoef, 0);
*/
    //TODO reset _vx = 0 when it becomes insignificant

    //out << "vx: " << _vx << " , vy: " << _vy << "\n";

    _y += _vy;
    if (!(onLadder && collidingObjects.size() > 1))
        _x += _vx;

    //setPos(_x, _y);
}
