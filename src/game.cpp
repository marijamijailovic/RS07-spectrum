#include "include/game.h"

SpectrumGame::SpectrumGame(QGraphicsScene *scene) :
    _scene(scene)
{

    // Creating a player and adding to scene
    _player = new Player(200, 180);
    _scene->addItem(_player);
    _scene->setBackgroundBrush(QBrush(_player->activeColor()));

    // Creating new level
    _level = new Level(":levels/001.lvl", _player);
    _level->load(_scene);

    // Creating timer for gravity function
    _gameTicker = new QTimer();
    connect(_gameTicker, SIGNAL(timeout()), this, SLOT(update()));
    _gameTicker->start(40);
}

SpectrumGame::~SpectrumGame()
{
    _gameTicker->stop();
    delete _gameTicker;
    delete _player;
    delete _level;
}

void SpectrumGame::update() const
{
    _player->move();
    std::vector<DynamicEntity *> dynamicEntities = _level->DynamicEntities();
    foreach (DynamicEntity *ent, dynamicEntities) {
        ent->move();
        ent->applyGravity(_gravCoeff);
    }
    _player->applyGravity(_gravCoeff);
    _level->applyGravity(_gravCoeff);
}
