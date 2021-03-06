#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QTimer>
#include <vector>
#include "include/entity.h"
#include "include/door.h"
#include "include/colors.h"


class Key : public Entity
{
    Q_OBJECT

public:
    Key(qreal x, qreal y,
        Door *door,
        const QColor color = SpectrumColors::gray);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void collect();

signals:
    void collected();

private slots:
    void updateSparklesPos();

private:
    void unlockDoor();
    void lockDoor();

    Door *_door;
    QScopedPointer<QTimer> _sparkTicker;
    const unsigned _sparkNum = 5;
    std::vector<int> _sx {0, 0, 0, 0, 0};
    std::vector<int> _sy {0, 0, 0, 0, 0};
};

#endif // KEY_H
