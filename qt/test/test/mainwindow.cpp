#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->ChagneButton,SIGNAL(clicked()),this,SLOT(setTitle()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTitle()
{
    this->setWindowTitle("thifdssdfs");
}
