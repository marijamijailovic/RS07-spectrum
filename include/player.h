#ifndef PLAYER_H
#define PLAYER_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include "include/dynamicentity.h"

class Player : public DynamicEntity
{
public:
    Player(qreal x, qreal y);

    QColor activeColor() const;

    void keyPressEvent(QKeyEvent *event) override;

    // Overrides from Entity
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Overrides from DynamicEntity
    void applyGravity(qreal g);
    void move();
private:
    bool _jump = false;
    int _canJump = 2;
    QColor _activeColor = Qt::blue;
};

#endif // PLAYER_H
