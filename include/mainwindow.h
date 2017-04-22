#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include/game.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // TODO delete operator= and copy-constructor

private:
    Ui::MainWindow *_ui;
    SpectrumGame *_game;
};

#endif // MAINWINDOW_H
