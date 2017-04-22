#include "include/player.h"

Player::Player(qreal x, qreal y) :
    QGraphicsEllipseItem(x, y, 50, 50),
    DynamicEntity::DynamicEntity(x, y, 0),
    _jumpInProgress(false)
{
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
        drawAt(x() - 10, y());
    else if (event->key() == Qt::Key_Right)
        drawAt(x() + 10, y());
    // TODO
    // Add jump
}

void Player::drawAt(qreal x, qreal y)
{
    _x = x;
    _y = y;
    setPos(x, y);
}
