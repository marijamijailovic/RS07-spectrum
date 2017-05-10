#include "include/game.h"

SpectrumGame::SpectrumGame(QGraphicsView *parent) :
    _paused(false),
    _expandInProgress(false),
    _parent(parent),
    _player(new Player(200, 180)),
    _background(new Background()),
    _level(new Level(":levels/test.lvl", *_player, &_activeColor)),
    _gameTicker(new QTimer())
{
    //addItem(&(*_background)); // TODO Find a nice background picture

    // Adding player to the scene
    addItem(&(*_player));
    setBackgroundBrush(QBrush(_activeColor));

    // Loading new level
    _level->load(this);

    // Connecting timer to game-tick function
    connect(&(*_gameTicker), SIGNAL(timeout()), this, SLOT(update()));
    _gameTicker->start(40);

    // Setting focus to scene
    setFocus();
}

SpectrumGame::~SpectrumGame()
{
    _gameTicker->stop();
}

void SpectrumGame::loadLevel(const QString id)
{
    _level.reset(new Level(":levels/" + id + ".lvl", *_player, &_activeColor));
    _level->load(this);
    setBackgroundBrush(QBrush(_activeColor));
}

void SpectrumGame::pause()
{
    _gameTicker->stop();
    _paused = true;
    clearFocus();
    _parent->hide();
}

void SpectrumGame::resume()
{
    _gameTicker->start();
    _paused = false;
}

void SpectrumGame::keyPressEvent(QKeyEvent *event)
{
    if (_paused)
        return;

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
    else // TODO add check for numbers
        changeActiveColor(event);
}

void SpectrumGame::changeActiveColor(QKeyEvent *event)
{
    QColor newActiveColor = _activeColor;
    if (event->key() == Qt::Key_1)
        newActiveColor = SpectrumColors::blue;
    else if (event->key() == Qt::Key_2)
        newActiveColor = SpectrumColors::green;
    else if (event->key() == Qt::Key_3)
        newActiveColor = SpectrumColors::yellow;
    else if (event->key() == Qt::Key_4)
        newActiveColor = SpectrumColors::red;
    else if (event->key() == Qt::Key_5)
        newActiveColor = SpectrumColors::orange;
    else if (event->key() == Qt::Key_6)
        newActiveColor = SpectrumColors::purple;
    else if (event->key() == Qt::Key_7)
        newActiveColor = SpectrumColors::pink;

    // If the chosen new active color is the same as the one before, do nothing
    if (newActiveColor == _activeColor)
        return;

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
        _activeColor = newActiveColor;
        if (!_expandInProgress)
            animateColorChange();
        update();
    }

    hideObjectsWithActiveColor();
}

void SpectrumGame::animateColorChange()
{
    _expandInProgress = true;
    _colorCircle.reset(new ColorChanger(_parent, _player->x(), _player->y(), _activeColor));
    addItem(&(*_colorCircle));
    _parent->update();
    QTimer::singleShot(400, this, SLOT(stopColorChangeAnimation()));
}

void SpectrumGame::stopColorChangeAnimation()
{
    if (_expandInProgress)
        removeItem(&(*_colorCircle));
    setBackgroundBrush(QBrush(_activeColor));
    _expandInProgress = false;
}

void SpectrumGame::hideObjectsWithActiveColor()
{
    // Hide objects from the scene that have the same color as activeColor
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
    _parent->update();
}
