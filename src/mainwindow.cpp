#include "ui_mainwindow.h"
#include "include/mainwindow.h"

#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _ui->frLevelTree->hide();

    // TODO show menu on start (hide resume game)
    _game.reset(new SpectrumGame(_ui->gwDisplay));
    initializeGameWindow();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::on_btnResumeGame_clicked()
{
    _game->resume();
    _ui->gwDisplay->show();
    _ui->gwDisplay->setFocus();
    _ui->frLevelTree->hide();
}

void MainWindow::on_btnExit_clicked()
{
    exit(EXIT_SUCCESS);
}

void MainWindow::on_btnNewGame_clicked()
{
    _game.reset(new SpectrumGame(_ui->gwDisplay));
    initializeGameWindow();

    _ui->gwDisplay->show();
    _ui->gwDisplay->setFocus();
}

void MainWindow::initializeGameWindow()
{
    _ui->gwDisplay->setScene(&(*_game));
    _ui->gwDisplay->raise();
    _ui->gwDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _ui->gwDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::on_btnChooseLevel_clicked()
{
    _ui->frLevelTree->show();
}

void MainWindow::on_pbLevelDemo_clicked()
{
    _game->loadLevel("test");
    _ui->btnResumeGame->click();
}

void MainWindow::on_pbLevel1_clicked()
{
    _game->loadLevel("001");
    _ui->btnResumeGame->click();
}

void MainWindow::on_pbLevel2_clicked()
{
    _game->loadLevel("002");
    _ui->btnResumeGame->click();
}

void MainWindow::on_pbLevel3_clicked()
{
    _game->loadLevel("003");
    _ui->btnResumeGame->click();
}

void MainWindow::on_pbHideLevelPanel_clicked()
{
    _ui->frLevelTree->hide();
}
