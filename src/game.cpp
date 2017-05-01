#include "include/game.h"

SpectrumGame::SpectrumGame()
{
    // Creating a player and adding to scene
    _player = new Player(200, 180);
    addItem(_player);
    setBackgroundBrush(QBrush(_activeColor));

    // Creating new level
    _level = new Level(":levels/test.lvl", _player);
    _level->load(this);

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

void SpectrumGame::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
        _player->applyForce(-8,0);
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
        _player->applyForce(8,0);
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
        _player->setJump(true);
    else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
        ;//_player->_vx = 0;
    else if (event->key() == Qt::Key_Escape)    // TODO remove exit on ESC
        exit(EXIT_SUCCESS);
    else
        changeActiveColor(event);
}

void SpectrumGame::changeActiveColor(QKeyEvent *event)
{
    // Disable changing active color when there's a collision with entities with activeColor
    QList<QGraphicsItem *> collidingObjects = _player->collidingItems();
    foreach (QGraphicsItem* item, collidingObjects)
        if (((Entity*)item)->collidable() && _activeColor == ((Entity*)item)->color())
            return;

    if (event->key() == Qt::Key_1)
        _activeColor = SpectrumColors::blue;
    else if (event->key() == Qt::Key_2)
        _activeColor = SpectrumColors::green;
    else if (event->key() == Qt::Key_3)
        _activeColor = SpectrumColors::yellow;
    else if (event->key() == Qt::Key_4)
        _activeColor = SpectrumColors::red;
    else if (event->key() == Qt::Key_5)
        _activeColor = SpectrumColors::orange;
    else if (event->key() == Qt::Key_6)
        _activeColor = SpectrumColors::purple;
    else if (event->key() == Qt::Key_7)
        _activeColor = SpectrumColors::pink;

    update();
    setBackgroundBrush(QBrush(_activeColor));
}

void SpectrumGame::update() const
{
    _player->move(_activeColor);
    std::vector<DynamicEntity *> dynamicEntities = _level->DynamicEntities();
    foreach (DynamicEntity *ent, dynamicEntities) {
        ent->move(_activeColor);
        ent->applyGravity(_gravCoeff);
    }
    _player->applyGravity(_gravCoeff);
    _level->applyGravity(_gravCoeff);
}
