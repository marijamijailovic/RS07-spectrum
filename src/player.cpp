#include "include/player.h"
#include <QTextStream>
Player::Player(qreal x, qreal y) :
    DynamicEntity::DynamicEntity(x, y, 50)
{
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
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
    return QRectF(-30, -50, 60, 100);
}

QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addRect(-30, -50, 60, 100);
    return path;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
        _vx = -10;
    if (event->key() == Qt::Key_Right)
        _vx = 10;
    if (event->key() == Qt::Key_Up) {
        if(_inAir)
            _jump = true;
        else {
            _vy = -10;
            _inAir = true;
        }
    }
    QTextStream out(stdout);
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
    } else if (event->key() == Qt::Key_Escape) { // TODO remove
        exit(EXIT_SUCCESS);
    }

}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(_activeColor);
    painter->drawRect(-30, -50, 60, 100);
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
void Player::applyGravity(qreal g){
    applyForce(0, g);
}

void Player::move()
{
    QTextStream out(stdout);
    QList<QGraphicsItem *> collidingObjects = collidingItems();
    foreach (QGraphicsItem *item, collidingObjects) {
        QRectF a = mapToScene(this->boundingRect()).boundingRect();
        QRectF b = item->boundingRect();
        if(_vy >= 0 && a.bottom() > b.top() && _vy >= a.bottom() - b.top()){
            _y += b.top() - a.bottom() + 0.9145;
            //out << "bottom";
        }
        else if(_vx != 0 && a.right() > b.left() && a.right() - b.left() < _vx){
            _x += b.left() - a.right() - 1;
            _vx = 0;
            //out << "right";
        }
        else if(_vx != 0 && a.left() < b.right() && b.right() - a.left() < -_vx){
            _x += b.right() - a.left() + 1;
            _vx = 0;
            //out << "left";
        }
     }

    //purpose of canJump is wall jumping, currently disabled
    if (collidingObjects.isEmpty()) {
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
