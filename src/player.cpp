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
    _jump = (b && !_inAir);
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
    painter->drawPixmap(0, 0, _w, _h, _sprite.nextFrame());
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
    bool ladder=false;
    int ignoredCollisions = 0;
    QList<QGraphicsItem *> collidingObjects = collidingItems();
    foreach (QGraphicsItem *item, collidingObjects) {
        if ( !((Entity*)item)->collidable()) {
            ignoredCollisions++;
            continue;
        }
        if (typeid(*item) == typeid(Ladder)) {
            ladder=true;
        }
    }
    if(!ladder)onLadder=false;
    if (collidingObjects.size() == ignoredCollisions){
        return true;
    }
    if(ladder){
        if(!onLadder){
            moveBy(0,-1);
            onLadder=true;
        }
        int oldColl = (collidingObjects.size())-ignoredCollisions;
        if(_up&&!_left&&!_right)moveBy(0,-1);
        if(_down&&!_left&&!_right)moveBy(0, 1);
        if(_left) moveBy(-1,0);
        if(_right) moveBy(1,0);
        QList<QGraphicsItem *> collidingObjects = collidingItems();
        foreach (QGraphicsItem *item, collidingObjects) {
            if ( !((Entity*)item)->collidable()) {
                ignoredCollisions++;
                continue;
            }
        }
        if(oldColl >= (collidingObjects.size())-ignoredCollisions);
        else {
            if(_up&&!_left&&!_right)moveBy(0,1);
            if(_down&&!_left&&!_right)moveBy(0,-1);
            if(_left) moveBy(1,0);
            if(_right) moveBy(-1,0);
        }
    }

    return false;
}
void Player::jump(){

    QTextStream out(stdout);
    if(_jump&&!_inAir) {
        _vy=-15;
        _jump=false;
    }
}

void Player::movement(){
    if (_left)
        applyForce(-1200,0);
    if (_right)
        applyForce(1200,0);
    QList<QGraphicsItem *> collidingObjects = collidingItems();
    int ignoredCollisions = 0;
    foreach (QGraphicsItem *item, collidingObjects) {
        if ( !((Entity*)item)->collidable()) {
            ignoredCollisions++;
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

        if (typeid(*item) == typeid(Ladder)) {
            ignoredCollisions++;
        }
    }
}
