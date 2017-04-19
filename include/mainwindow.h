#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include/game.h"

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
    SpectrumGame *_game;
};

#endif // MAINWINDOW_H
