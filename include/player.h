#ifndef PLAYER_H
#define PLAYER_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <typeinfo>
#include "include/dynamicentity.h"
#include "include/key.h"
#include "include/colorunlocker.h"


class Player : public DynamicEntity
{
public:
    Player(qreal x, qreal y);

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    void setJump(bool b);
    void setLeft(bool b);
    void setRight(bool b);

    // Overrides from Entity
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qreal centerX() const override;
    qreal centerY() const override;

    // Overrides from DynamicEntity
    void move();

private:
    const int _w = 60;
    const int _h = 77;
    bool _jump = false;
    int _canJump = 2;
    // Key press detection for moving
    bool _up = false;
    bool _down = false;
    bool _right = false;
    bool _left = false;
};

#endif // PLAYER_H
