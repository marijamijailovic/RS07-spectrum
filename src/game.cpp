#include "include/game.h"

SpectrumGame::SpectrumGame(QGraphicsView *parent) :
    _paused(false),
    _expandInProgress(false),
    _parent(parent),
    _activeColor(SpectrumColors::defaultActiveColor),
    _player(new Player(0, 0)),
    _spectrum(new ColorChooser(0, 0, _unlockedColors)),
    _gameTicker(new QTimer()),
    _unlockedColors {true, false, false, false, false, false}
    //_unlockedColors {true, true, true, true, true, true} // TODO remove before release
{
    // Adding color chooser to the scene
    addItem(&(*_spectrum));
    _spectrum->hide();

    // Loading new level
    loadLevel("test");

    // Adding player to the scene
    addItem(&(*_player));

    // Connecting timer to game-tick function
    connect(&(*_gameTicker), SIGNAL(timeout()), this, SLOT(update()));
    _gameTicker->start(15);

    // Setting focus to scene
    setFocus();
}

SpectrumGame::~SpectrumGame()
{
    _gameTicker->stop();
}

void SpectrumGame::loadLevel(const QString id)
{
    // Load next level
    _level.reset(new Level(":levels/" + id + ".lvl", *_player, &_activeColor));
    _level->load(this);
    setBackgroundBrush(QBrush(_activeColor));

    // Stop player
    _player->setVx(0);
    _player->setVy(0);

    // Connecting slots
    connectSlots(_level->staticEntities());
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
        _player->setLeft(true);
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
        _player->setRight(true);
    else if (event->key() == Qt::Key_Space)
        _player->setJump(true);
    else if (event->key() == Qt::Key_Z)
        _player->setPull(true);
    else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S) {
        _player->setDown(true);
        _player->setVx(0);
    } else if (event->key() == Qt::Key_P)
        pause();
    else if (event->key() == Qt::Key_Escape)    // TODO remove exit on ESC
        exit(EXIT_SUCCESS);
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
        _player->setUp(true); // ladders
    else if (event->key() == Qt::Key_E)
        interact();
    else // TODO add check for numbers
        if (!_expandInProgress)
            changeActiveColor(event);
}

void SpectrumGame::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
        _player->setLeft(false);
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
        _player->setRight(false);
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
        _player->setUp(false);
    else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
        _player->setDown(false);
    else if (event->key() == Qt::Key_Z)
        _player->setPull(false);
}

void SpectrumGame::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    foreach (QGraphicsItem* item, items())
        if (((Entity*)item)->color() == _activeColor)
            item->show();
    animateColorChange(SpectrumColors::gray);
    _spectrum->show();
}

void SpectrumGame::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    QPointF mouseReleasePos = e->lastScenePos();
    int colorID = _spectrum->determineColorID(mouseReleasePos);
    if (isUnlocked(colorID))
        animateColorChange(SpectrumColors::getColorFromID(colorID));
    else
        animateColorChange(SpectrumColors::blue);
    _spectrum->hide();
}

void SpectrumGame::changeActiveColor(QKeyEvent *event)
{
    QColor newActiveColor = _activeColor;
    if (event->key() == Qt::Key_1 && _unlockedColors[SpectrumColors::BLUE])
        newActiveColor = SpectrumColors::blue;
    else if (event->key() == Qt::Key_2 && _unlockedColors[SpectrumColors::GREEN])
        newActiveColor = SpectrumColors::green;
    else if (event->key() == Qt::Key_3 && _unlockedColors[SpectrumColors::YELLOW])
        newActiveColor = SpectrumColors::yellow;
    else if (event->key() == Qt::Key_4 && _unlockedColors[SpectrumColors::RED])
        newActiveColor = SpectrumColors::red;
    else if (event->key() == Qt::Key_5 && _unlockedColors[SpectrumColors::ORANGE])
        newActiveColor = SpectrumColors::orange;
    else if (event->key() == Qt::Key_6 && _unlockedColors[SpectrumColors::PURPLE])
        newActiveColor = SpectrumColors::purple;

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
        if (!_expandInProgress)
            animateColorChange(newActiveColor);
        update();
    }

}

void SpectrumGame::interact()
{
    foreach (QGraphicsItem *item, _player->collidingItems()) {
        // Try to cast the colliding object to class Door
        // If the result is not nullptr, then go through the door if it's unlocked
        Door *door = qobject_cast<Door *>((Entity *)item);
        if (door != nullptr) {
            if (!door->isLocked())
                loadLevel(door->nextLevel());
            break;
        }
    }
}

void SpectrumGame::unlockColor(int id)
{
    _unlockedColors[id] = true;
}

bool SpectrumGame::isUnlocked(const QColor &color) const
{
    return _unlockedColors[SpectrumColors::toEnum(color)];
}

bool SpectrumGame::isUnlocked(int colorID) const
{
    return _unlockedColors[colorID];
}

void SpectrumGame::animateColorChange(QColor color)
{
    _activeColor = color;
    _expandInProgress = true;
    _colorCircle.reset(new ColorChanger(_parent, _player->centerX(), _player->centerY(), color));
    connect(&(*_colorCircle), SIGNAL(expandingDone()), this, SLOT(stopColorChangeAnimation()));
    addItem(&(*_colorCircle));
    _parent->update();
}

void SpectrumGame::stopColorChangeAnimation()
{
    if (_expandInProgress)
        removeItem(&(*_colorCircle));
    setBackgroundBrush(_activeColor);
    _expandInProgress = false;
    if (_activeColor != SpectrumColors::gray)
        hideObjectsWithActiveColor();
}

void SpectrumGame::connectSlots(std::vector<Entity *> entities)
{
    foreach (QGraphicsItem *item, entities) {
        if (typeid(*item) == typeid(ColorUnlocker)) {
            if (isUnlocked(((ColorUnlocker*)item)->color())) {
                removeItem(item);
            } else
                connect((ColorUnlocker*)item, SIGNAL(colorUnlocked(int)), this, SLOT(unlockColor(int)));
        }
    }
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

    QTextStream out(stdout);
    //out<<_level->dynamicEntities().size();
        _player->jump();
    _player->movement();

    std::vector<DynamicEntity *> dynamicEntities = _level->dynamicEntities();
    foreach (DynamicEntity *ent, dynamicEntities){
        ent->setCh(0);
    }

    while(true){
        int i=0;
    int min=0;
    double minch=2;
    foreach (DynamicEntity *ent, dynamicEntities) {
        if(ent->getCh()<minch){
            min=i;
            minch=ent->getCh();
        }
        i++;
    }
    if(minch>=1) break;
    DynamicEntity *ent = dynamicEntities.at(min);
    ent->move(min);
    }
    _player->applyGravity(_gravCoeff);
    _level->applyGravity(_gravCoeff);
    _spectrum->setPos(_player->centerX(), _player->centerY());
    _parent->update();
}
