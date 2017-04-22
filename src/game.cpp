#include "include/game.h"

SpectrumGame::SpectrumGame(QGraphicsScene *scene) :
    _scene(scene)
{
    // Creating a player and adding to scene
    _player = new Player(0, 0);
    _scene->addItem(_player);

    // Creating new level
    _level = new Level();
    _level->load(_scene);
}

SpectrumGame::~SpectrumGame()
{
    delete _player;
    delete _level;
}
