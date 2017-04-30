#include "include/player.h"
#include <QBrush>
#include <QPixmap>
#include <QTextStream>

Player::Player(qreal x, qreal y) :
    DynamicEntity::DynamicEntity(x, y, 1)
{
    setZValue(1);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

QColor Player::activeColor() const
{
    return _activeColor;
}

void Player::setActiveColor(QColor newActiveColor)
{
    _activeColor = newActiveColor;
}

QRectF Player::boundingRect() const
{
    return QRectF(-_w/2, -_h/2, _w, _h);
}

QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addRect(-_w/2, -_h/2, _w, _h);
    return path;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
        applyForce(-8,0);
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
        applyForce(8,0);
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
        _jump = true;
    else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
        _vx = 0;
    else if (event->key() == Qt::Key_Escape)    // TODO remove exit on ESC
        exit(EXIT_SUCCESS);
    else
        changeActiveColor(event);
}

void Player::changeActiveColor(QKeyEvent *event)
{
    // Disable changing active color when there's a collision with entities with activeColor
    QList<QGraphicsItem *> collidingObjects = collidingItems();
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
    scene()->setBackgroundBrush(QBrush(_activeColor));
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-_w/2, -_h/2, _w, _h, QPixmap(":sprites/astronaut.png"));
}

void Player::move()
{
    QTextStream out(stdout);
    QList<QGraphicsItem *> collidingObjects = collidingItems();
    int ignoredCollisions = 0;
    foreach (QGraphicsItem *item, collidingObjects) {
        if ( !((Entity*)item)->collidable() || _activeColor == ((Entity*)item)->color()) {
            ignoredCollisions++;
            //out << "no collision\n";
            continue;
        }
        // If the item is a key, collect it and unlock the binded door
        if (typeid(*item) == typeid(Key)) {
            ((Key*)item)->unlockDoor();
            // Redraw the door
            ((Key*)item)->door()->update();
            // Hide key from the scene
            // TODO: delete Key item from the scene (maybe ?)
            item->hide();
            ignoredCollisions++;
            continue;
        }
        QRectF a = mapToScene(boundingRect()).boundingRect();
        QRectF b = item->boundingRect();
        if (_vy >= 0 && a.bottom() > b.top() && _vy >= a.bottom() - b.top()) {
            _y += b.top() - a.bottom() + 0.9145;
            _canJump = 2;
            //out << "bottom";
        } else if(_vy <= 0 && a.top() < b.bottom() && 1 - _vy >= b.bottom() - a.top()) {
            _y += b.bottom() - a.top() + 0.9145;
            _vy = 0;
            _canJump = -1;
            _inAir = true;
            //out << "bottom";
        } else if(_vx != 0 && a.right() > b.left() && a.right() - b.left() < _vx + 1) {
            _x += b.left() - a.right() - 1;
            _vx = 0;
            //out << "right";
        } else if(_vx != 0 && a.left() < b.right() && b.right() - a.left() < -_vx + 1) {
            _x += b.right() - a.left() + 1;
            _vx = 0;
            //out << "left";
        }
    }

    //purpose of canJump is wall jumping, currently disabled
    if (collidingObjects.size() == ignoredCollisions) {
        _inAir = true;
        if(_canJump)
            _canJump--;
    } else if (_jump && _canJump > 0) {
        _jump = false;
        _inAir = true;
        _vy = -10;
    } else if (_canJump < 0) {
        if (!_inAir)
            _canJump = 0;
    } else {
        _inAir = false;
        _jump = false;
        if (_vy > 0)
            _vy = 0;
    }

    if (_canJump == 0)
        _jump = false;
    _y += _vy;
    _x += _vx;
    applyForce(-_vx*0.03,0);    // Air resistance

    if (_inAir == false)
        applyForce(-_vx*0.1,0); // Friction

    drawAt(_x, _y);
}
