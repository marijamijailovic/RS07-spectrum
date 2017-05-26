#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>
#include <QtGlobal>
#include <QObject>
#include <QTimer>

class Sprite : QObject
{
    Q_OBJECT

public:
    Sprite();
    bool animationActive() const;
    QPixmap nextFrame() const;
    void addFrame(const QString& frame);

private slots:
    void change();

private:
    std::vector<QPixmap> _sprites;
    unsigned _current;
    bool _animationActive;
    bool _ind;
    QTimer _ticker;
};

#endif // SPRITE_H
