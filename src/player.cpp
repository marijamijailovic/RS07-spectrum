#include "include/player.h"
#include <QBrush>
#include <QPixmap>
#include <QTextStream>

Player::Player(qreal x, qreal y) :
    DynamicEntity::DynamicEntity(x, y, 50)
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
    if (event->key() == Qt::Key_Left)
        _vx = -10;
    else if (event->key() == Qt::Key_Right)
        _vx = 10;
    else if (event->key() == Qt::Key_Up) {
        if(_inAir)
            _jump = true;
        else {
            _vy = -10;
            _inAir = true;
        }
    }
    // TODO remove exit on Esc
    else if (event->key() == Qt::Key_Escape) {
        exit(EXIT_SUCCESS);
    }
    else {
        QTextStream out(stdout);
        // Disable changing active color when there's a collision with entities with activeColor
        QList<QGraphicsItem *> collidingObjects = collidingItems();
        foreach (QGraphicsItem* item, collidingObjects) {
            if (_activeColor == ((Entity*)item)->color()) {
                out << "Changing active color disabled\n";
                return;
            }
        }
        if (event->key() == Qt::Key_1) {
            _activeColor = Qt::blue;
            out << "Active color: blue\n";
        } else if (event->key() == Qt::Key_2) {
            _activeColor = Qt::green;
            out << "Active color: green\n";
        } else if (event->key() == Qt::Key_3) {
            _activeColor = Qt::yellow;
            out << "Active color: yellow\n";
        } else if (event->key() == Qt::Key_4) {
            _activeColor = Qt::red;
            out << "Active color: red\n";
        }
        update();
        scene()->setBackgroundBrush(QBrush(_activeColor));
    }
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-_w/2, -_h/2, _w, _h, QPixmap(":sprites/player.png"));
}

void Player::move()
{
    QTextStream out(stdout);
    QList<QGraphicsItem *> collidingObjects = collidingItems();
    int sameColorCollisions = 0;
    foreach (QGraphicsItem *item, collidingObjects) {
        if (_activeColor == ((Entity*)item)->color()) {
            sameColorCollisions++;
            //out << "no collision\n";
            continue;
        }
        QRectF a = mapToScene(this->boundingRect()).boundingRect();
        QRectF b = item->boundingRect();
        if(_vy >= 0 && a.bottom() > b.top() && _vy >= a.bottom() - b.top()){
            _y += b.top() - a.bottom() + 0.9145;
            //out << "bottom";
        }
        else if(_vx != 0 && a.right() > b.left() && a.right() - b.left() < _vx+1){
            _x += b.left() - a.right() - 1;
            _vx = 0;
            //out << "right";
        }
        else if(_vx != 0 && a.left() < b.right() && b.right() - a.left() < -_vx+1){
            _x += b.right() - a.left() + 1;
            _vx = 0;
            //out << "left";
        }
     }

    //purpose of canJump is wall jumping, currently disabled
    if (collidingObjects.size() == sameColorCollisions) {
        _inAir = true;
        if(_canJump)
            _canJump--;
    } else if(_jump && _canJump) {
        _jump = false;
        _inAir = true;
        _vy = -10;
    } else {
        _inAir = false;
        _jump = false;
        if (_vy > 0)
            _vy = 0;
        _canJump = 2;
    }
    _y += _vy;
    _x += _vx;
    _vx *= 0.9145;
    drawAt(_x, _y);
}
