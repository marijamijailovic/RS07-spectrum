#ifndef PLAYER_H
#define PLAYER_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <typeinfo>
#include "include/dynamicentity.h"
#include "include/key.h"


class Player : public DynamicEntity
{
public:
    Player(qreal x, qreal y);

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    void setJump(bool b);

    // Overrides from Entity
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Overrides from DynamicEntity
    void move(const QColor activeColor);

private:
    const int _w = 60;
    const int _h = 77;
    bool _jump = false;
    int _canJump = 2;
};

#endif // PLAYER_H
