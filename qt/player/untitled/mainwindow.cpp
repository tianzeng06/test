#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->timer=new QTimer;
    QObject::connect(this->timer,SIGNAL(timeout()),this,SLOT(fetchPrictureSlot()));
    this->timer->start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fetchPrictureSlot()
{
    QClipboard *board=QApplication::clipboard();
    this->pixmap=board->pixmap();
    ui->playerLabel->setPixmap(this->pixmap.scaled(ui->playerLabel->size()));
    return ;
}
