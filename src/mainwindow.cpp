#include "ui_mainwindow.h"
#include "include/mainwindow.h"

#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _game = new SpectrumGame(_ui->gwDisplay);
    initializeGameWindow();
}

MainWindow::~MainWindow()
{
    delete _game;
    delete _ui;
}

void MainWindow::on_btnResumeGame_clicked()
{
    _game->resume();
}

void MainWindow::on_btnExit_clicked()
{
    exit(EXIT_SUCCESS);
}

void MainWindow::on_btnNewGame_clicked()
{
    delete _game;
    _game = new SpectrumGame(_ui->gwDisplay);
    initializeGameWindow();

    _ui->gwDisplay->show();
    _ui->gwDisplay->setFocus();
}

void MainWindow::initializeGameWindow()
{
    _ui->gwDisplay->setScene(_game);
    _ui->gwDisplay->raise();
    _ui->gwDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _ui->gwDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
