#include "include/player.h"

Player::Player(qreal x, qreal y) :
    QGraphicsEllipseItem(x, y, 50, 50),
    DynamicEntity::DynamicEntity(x, y, 5),
    _jumpInProgress(false)
{
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
        this->setPos(x() - 10, y());
    else if (event->key() == Qt::Key_Right)
        this->setPos(x() + 10, y());
    // TODO
    // Add jump
}
