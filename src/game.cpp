#include "include/game.h"

SpectrumGame::SpectrumGame(QGraphicsScene *scene) :
    _scene(scene)
{
    // Creating a player and adding to scene
    _player = new Player(200, 180);
    _scene->addItem(_player);

    // Creating new level
    _level = new Level(":levels/001.lvl", _player);
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
    std::vector<DynamicEntity *> dynamicEntities = _level->DynamicEntities();
    foreach (DynamicEntity *ent, dynamicEntities) {
        ent->move();
        ent->applyGravity(_gravCoeff);
    }
    _player->applyGravity(_gravCoeff);
    _level->applyGravity(_gravCoeff);
}
