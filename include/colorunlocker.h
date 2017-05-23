#ifndef COLORUNLOCKER_H
#define COLORUNLOCKER_H

#include <QObject>
#include <QTimer>
#include "include/entity.h"


class ColorUnlocker : public Entity
{
    Q_OBJECT

public:
    ColorUnlocker(qreal x, qreal y,
                  const QColor color);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void collect();

signals:
    void colorUnlocked(int id);

private slots:
    void incrementOpacity();
    void raise();

private:
    int _opacity;
    int _step;
    qreal _raiseH;
    QScopedPointer<QTimer> _opacityTicker;
    QScopedPointer<QTimer> _raiseTicker;
};

#endif // COLORUNLOCKER_H
