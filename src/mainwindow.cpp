#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Creating a test scene
    QGraphicsScene *scene = new QGraphicsScene();

    // Creating a rectangle
    QGraphicsRectItem *rect = new QGraphicsRectItem();
    rect->setRect(0,0,50,50);

    // Add the rectangle into the scene
    scene->addItem(rect);

    // Add scene to main display widget
    ui->gwDisplay->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
