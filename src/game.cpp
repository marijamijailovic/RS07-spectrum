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

    // Creating timer for gravity function
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(applyGravity()));
    timer->start(50);
}

SpectrumGame::~SpectrumGame()
{
    delete _player;
    delete _level;
}

void SpectrumGame::applyGravity() const
{
    bool updatePlayer = true;
    std::vector<Block *> entities = _level->getStaticEntities();
    for (unsigned i = 0; i < entities.size(); i++)
        if (_player->getYPos() + 50 == entities[i]->getYPos())  // FIXME, temp
            updatePlayer = false;

    if (updatePlayer)
        _player->applyGravity(_gravCoeff);
    _level->applyGravity(_gravCoeff);
}
