#include "include/player.h"

Player::Player(QGraphicsScene *scene, int x, int y)
{
    // Creating a player
    _player = new QGraphicsRectItem();
    _player->setRect(x, y, 20, 50);

    _scene = scene;

    // Add the rectangle into the scene
    _scene->addItem(_player);
}

Player::~Player()
{
    _scene->removeItem(_player);
    delete _player;
}
