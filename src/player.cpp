#include "include/player.h"

Player::Player(int x, int y) :
    QGraphicsEllipseItem(x, y, 50, 50)
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
}
