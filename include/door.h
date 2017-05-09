#ifndef DOOR_H
#define DOOR_H

#include "include/colors.h"
#include "include/entity.h"

class Door : public Entity
{
public:
    Door(qreal x, qreal y, const QString& nextLevel, const QColor color = SpectrumColors::gray, bool locked = false);

    // Overrides from QGraphicsItem
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void lock();
    void unlock();
    QString nextLevel() const;

private:
    const int _w = 60;
    const int _h = 100;
    bool _locked;
    QString _nextLevel = "laalala";
};

#endif // DOOR_H
