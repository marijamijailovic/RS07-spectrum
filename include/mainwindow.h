#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include "include/game.h"


extern QScopedPointer<SpectrumGame> _game;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;

private slots:
    void resumeGame();
    void newGame();
    void closeApp();
    void showLevelTree();
    void hideLevelTree();
    void levelLoad();

private:
    void initializeGameWindow();

    Ui::MainWindow *_ui;
};

#endif // MAINWINDOW_H
