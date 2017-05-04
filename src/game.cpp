#include "include/game.h"

SpectrumGame::SpectrumGame(QGraphicsView *parent) :
    _parent(parent),
    _player(new Player(200, 180)),
    _level(new Level(":levels/test.lvl", *_player))
{
    // Creating a player and adding to scene
    addItem(&(*_player));
    setBackgroundBrush(QBrush(_activeColor));

    // Loading new level
    _level->load(this);

    // Creating timer for gravity function
    _gameTicker = new QTimer();
    connect(_gameTicker, SIGNAL(timeout()), this, SLOT(update()));
    _gameTicker->start(40);

    setFocus();
}

SpectrumGame::~SpectrumGame()
{
    _gameTicker->stop();
    delete _gameTicker;
}

void SpectrumGame::pause()
{
    _gameTicker->stop();
    clearFocus();
    _parent->hide();
}

void SpectrumGame::resume()
{
    _gameTicker->start();
    setFocus();
    _parent->show();
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
        _player->setVx(0);
    else if (event->key() == Qt::Key_P)
        pause();
    else if (event->key() == Qt::Key_Escape)    // TODO remove exit on ESC
        exit(EXIT_SUCCESS);
    else
        changeActiveColor(event);
}

void SpectrumGame::changeActiveColor(QKeyEvent *event)
{
    /*
     * This is temporary solution with showing/hiding entities from the scene.
     * TODO
     * Make circle around the player and on mouse hover over one of them change the active color
     * In the meantime make gray (?) active color which will enable to check collisions with all items
     * on the scene
     */
    // Show all entities on the scene to be able to check collisions
    foreach (QGraphicsItem* item, items())
        if (((Entity*)item)->color() == _activeColor)
            item->show();

    // Disable changing active color when there's a collision with entities with activeColor
    QList<QGraphicsItem *> collidingObjects = _player->collidingItems();
    bool shouldChangeActiveColor = true;
    foreach (QGraphicsItem* item, collidingObjects)
        if (((Entity*)item)->collidable() && _activeColor == ((Entity*)item)->color()) {
            shouldChangeActiveColor = false;
            break;
        }

    if (shouldChangeActiveColor) {
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
    // Hide object from the scene that have the same color as activeColor
    foreach (QGraphicsItem* item, items())
        if (((Entity*)item)->color() == _activeColor)
            item->hide();
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
