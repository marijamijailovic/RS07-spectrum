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
    void on_btnResumeGame_clicked();
    void on_btnNewGame_clicked();
    void on_btnExit_clicked();
    void on_btnChooseLevel_clicked();
    void on_pbLevelDemo_clicked();
    void on_pbLevel1_clicked();
    void on_pbLevel2_clicked();
    void on_pbLevel3_clicked();
    void on_pbHideLevelPanel_clicked();

private:
    void initializeGameWindow();

    Ui::MainWindow *_ui;
    QScopedPointer<SpectrumGame> _game;
};

#endif // MAINWINDOW_H
