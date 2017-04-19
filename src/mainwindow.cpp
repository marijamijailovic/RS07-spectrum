#include "ui_mainwindow.h"
#include "include/mainwindow.h"
#include "include/player.h"

#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    // Creating a test scene
    QGraphicsScene *scene = new QGraphicsScene();

    // Creating a player
    _p = new Player(scene, 10, 10);

    // Add scene to main display widget
    _ui->gwDisplay->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete _ui;
}
