#include "include/player.h"
#include <QBrush>

Player::Player(qreal x, qreal y) :
    DynamicEntity::DynamicEntity(x, y, 60, 77, 1),
    _body(":/sprites/base.png"),
    _armsAndLegs(":/sprites/jump/jump00.png")
{
    setZValue(1);
    // Blinking
    _blinkSprite.addFrame(":/sprites/blink1.png");
    _blinkSprite.addFrame(":/sprites/blink2.png");
    _blinkSprite.addFrame(":/sprites/blink3.png");
    _blinkSprite.addFrame(":/sprites/blink4.png");
    _blinkSprite.addFrame(":/sprites/blink3.png");
    _blinkSprite.addFrame(":/sprites/blink2.png");
    _blinkSprite.addFrame(":/sprites/blink1.png");
    connect(&_blinkTicker, SIGNAL(timeout()), this, SLOT(blinkAnimation()));
    _blinkTicker.setInterval(3000);
    _blinkTicker.start();
    // Jumping
    _jumpSprite.addFrame(":/sprites/jump/jump01.png");
    _jumpSprite.addFrame(":/sprites/jump/jump02.png");
    _jumpSprite.addFrame(":/sprites/jump/jump03.png");
    _jumpSprite.addFrame(":/sprites/jump/jump04.png");
    _jumpSprite.addFrame(":/sprites/jump/jump05.png");
    _jumpSprite.addFrame(":/sprites/jump/jump06.png");
    _jumpSprite.addFrame(":/sprites/jump/jump07.png");
    _jumpSprite.addFrame(":/sprites/jump/jump08.png");
    _jumpSprite.addFrame(":/sprites/jump/jump09.png");
    _jumpSprite.addFrame(":/sprites/jump/jump10.png");
    _jumpSprite.addFrame(":/sprites/jump/jump11.png");
    _jumpSprite.addFrame(":/sprites/jump/jump12.png");
    _jumpSprite.setTickerInterval(70);
}

void Player::blinkAnimation()
{
    _blinkSprite.startAnimation();
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
    pull = b;
}

bool Player::getPull()
{
    return pull;
}

Sprite &Player::jumpSprite()
{
    return _jumpSprite;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, _w, _h, _body);
    if (_blinkSprite.animationActive())
        painter->drawPixmap(0, 0, _w, _h, _blinkSprite.nextFrame());
    if (_inAir)
        painter->drawPixmap(0, 0, _w, _h, _jumpSprite.nextFrame());
    else
        painter->drawPixmap(0, 0, _w, _h, _armsAndLegs);

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
