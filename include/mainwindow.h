#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include/player.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    Player *_p;
};

#endif // MAINWINDOW_H
