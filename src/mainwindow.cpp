#include "ui_mainwindow.h"
#include "include/mainwindow.h"
#include <QGraphicsScene>


QScopedPointer<SpectrumGame> _game;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _ui->frLevelTree->hide();

    // TODO show menu on start (hide resume game)
    _game.reset(new SpectrumGame(_ui->gwDisplay));

    // Set Antialiasing
    _ui->gwDisplay->setRenderHint(QPainter::Antialiasing);

    // Connecting singals to slots
    connect(_ui->btnResumeGame, SIGNAL(clicked()), this, SLOT(resumeGame()));
    connect(_ui->btnNewGame, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(_ui->btnExit, SIGNAL(clicked()), this, SLOT(closeApp()));
    connect(_ui->btnChooseLevel, SIGNAL(clicked()), this, SLOT(showLevelTree()));
    connect(_ui->pbHideLevelPanel, SIGNAL(clicked()), this, SLOT(hideLevelTree()));
    connect(_ui->pbLevel1, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel2, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel3, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevelDemo, SIGNAL(clicked()), this, SLOT(levelLoad()));

    initializeGameWindow();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::initializeGameWindow()
{
    _ui->gwDisplay->setScene(&(*_game));
    _ui->gwDisplay->raise();
    _ui->gwDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _ui->gwDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::resumeGame()
{
    _game->resume();
    _ui->gwDisplay->show();
    _ui->gwDisplay->setFocus();
    _ui->frLevelTree->hide();
}

void MainWindow::closeApp()
{
    // TODO :D
    exit(EXIT_SUCCESS);
}

void MainWindow::newGame()
{
    _game.reset(new SpectrumGame(_ui->gwDisplay));
    initializeGameWindow();

    _ui->gwDisplay->show();
    _ui->gwDisplay->setFocus();
}

void MainWindow::showLevelTree()
{
    _ui->frLevelTree->show();
}

void MainWindow::hideLevelTree()
{
    _ui->frLevelTree->hide();
}

void MainWindow::levelLoad()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    _game->loadLevel(btn->text());
    _ui->btnResumeGame->click();
}
