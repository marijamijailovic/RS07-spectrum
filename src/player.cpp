#include "include/player.h"
#include <QBrush>
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
    if (event->key() == Qt::Key_Left)
        applyForce(-8,0);
    else if (event->key() == Qt::Key_Right)
        applyForce(8,0);
    else if (event->key() == Qt::Key_Up) {
            _jump = true;
    }
    else if (event->key() == Qt::Key_Down) {
        _vx=0;
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
    painter->setBrush(_activeColor);
    painter->drawRect(-_w/2, -_h/2, _w, _h);
    painter->setBrush(Qt::black);
    painter->drawEllipse(-5, -32, 10, 10);
    painter->drawRect(-1, -22, 2, 34);
    painter->drawText(-28, -35, "Player");
    QPoint points[4];
    points[0] = QPoint(0, 12);
    points[1] = QPoint(12, 48);
    points[2] = QPoint(15, 50);
    points[3] = QPoint(3, 14);
    painter->drawPolygon(points, 4);
    points[0] = QPoint(0, 12);
    points[1] = QPoint(-12, 48);
    points[2] = QPoint(-15, 50);
    points[3] = QPoint(-3, 14);
    painter->drawPolygon(points, 4);
    points[0] = QPoint(0, -12);
    points[1] = QPoint(15, 0);
    points[2] = QPoint(18, 0);
    points[3] = QPoint(3, -14);
    painter->drawPolygon(points, 4);
    points[0] = QPoint(0, -12);
    points[1] = QPoint(-15, 0);
    points[2] = QPoint(-18, 0);
    points[3] = QPoint(-3, -14);
    painter->drawPolygon(points, 4);
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
            _canJump=2;
            //out << "bottom";
        }
        else if(_vy <= 0 && a.top() < b.bottom() && 1+-_vy >= b.bottom() - a.top()){
            _y += b.bottom() - a.top() + 0.9145;
            _vy = 0;
            _canJump = -1;
            _inAir = true;
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
    } else if(_jump && _canJump > 0) {
        _jump = false;
        _inAir = true;
        _vy = -10;
    } else if(_canJump < 0) {
        if(!_inAir)_canJump = 0;
    } else {
        _inAir = false;
        _jump = false;
        if (_vy > 0)
            _vy = 0;
    }
    if(_canJump == 0) _jump = false;
    _y += _vy;
    _x += _vx;
    applyForce(-_vx*0.03,0);    //air resistance
    if(_inAir==false) applyForce(-_vx*0.1,0);   //friction force
    drawAt(_x, _y);
}
