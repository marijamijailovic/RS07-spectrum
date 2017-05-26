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
    Sprite(const QString& defaultFrame);
    QPixmap nextFrame() const;
    void addFrame(const QString& frame);

private slots:
    void change();

private:
    std::vector<QPixmap> _sprites;
    QTimer _ticker;
    int _current;
    bool _ind = true;
};

#endif // SPRITE_H
