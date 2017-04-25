#include "include/game.h"

SpectrumGame::SpectrumGame(QGraphicsScene *scene) :
    _scene(scene)
{
    // Creating a player and adding to scene
    _player = new Player(200, 180);
    _scene->addItem(_player);

    // Creating new level
    _level = new Level(_player);
    _level->load(_scene);

    // Creating timer for gravity function
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(40);
}

SpectrumGame::~SpectrumGame()
{
    delete _player;
    delete _level;
}

void SpectrumGame::update() const
{
    _player->move();
    _player->applyGravity(_gravCoeff);
    _level->applyGravity(_gravCoeff);

}
