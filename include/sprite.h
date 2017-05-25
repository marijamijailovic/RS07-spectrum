#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>
#include <QtGlobal>
#include <QObject>
#include <QTimer>
#include <QScopedPointer>

class Sprite : QObject
{
    Q_OBJECT

public:
    Sprite();
    QPixmap nextFrame() const;

private slots:
    void change();

private:
    std::vector<QPixmap> _sprites;
    int _current;
    bool _ind = true;

    QTimer _ticker;
};

#endif // SPRITE_H
