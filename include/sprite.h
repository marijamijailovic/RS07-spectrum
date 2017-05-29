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
    void startAnimation();
    void stopAnimation();
    bool animationActive() const;
    bool inLoop() const;
    void setLoop(bool b);
    int tickerInterval() const;
    void setTickerInterval(int ms);
    QPixmap nextFrame() const;
    void addFrame(const QString& frame);

private slots:
    void change();

private:
    std::vector<QPixmap> _sprites;
    unsigned _current;
    bool _inLoop;
    QTimer _ticker;
};

#endif // SPRITE_H
