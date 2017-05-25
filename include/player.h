#ifndef PLAYER_H
#define PLAYER_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <typeinfo>
#include "include/dynamicentity.h"
#include "include/key.h"
#include "include/ladder.h"
#include "include/colorunlocker.h"
#include "include/sprite.h"


class Player : public DynamicEntity
{
public:
    Player(qreal x, qreal y);

    void setJump(bool b);
    void setLeft(bool b);
    void setRight(bool b);
    void setUp(bool b);
    void setDown(bool b);
    bool getPull();
    void setPull(bool b);
    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    qreal centerX() const override;
    qreal centerY() const override;

    // Overrides from DynamicEntity
    void movement();
    bool go();
    void jump();

private:
    bool _jump = false;
    int _canJump = 2;

    // Key press detection for moving
    bool _up = false;
    bool _down = false;
    bool _right = false;
    bool _left = false;
    bool pull=false;
    bool onLadder = false;

    Sprite _sprite;
};

#endif // PLAYER_H
