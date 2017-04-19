#include "ui_mainwindow.h"
#include "include/mainwindow.h"

#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    // Creating a test scene
    QGraphicsScene *scene = new QGraphicsScene();

    // Creating a new game on test scene
    _game = new SpectrumGame(scene);

    // Add scene to main display widget
    _ui->gwDisplay->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete _game;
    delete _ui;
}
