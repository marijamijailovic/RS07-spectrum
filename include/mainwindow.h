#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
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
    QScopedPointer<SpectrumGame> _game;
};

#endif // MAINWINDOW_H
