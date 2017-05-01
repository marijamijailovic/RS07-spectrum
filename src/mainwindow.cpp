#include "ui_mainwindow.h"
#include "include/mainwindow.h"

#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _game = new SpectrumGame(_ui->gwDisplay);

    _ui->gwDisplay->setScene(_game);
    _ui->gwDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _ui->gwDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
