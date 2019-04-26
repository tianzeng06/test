#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileButton_clicked()
{
    //if pocesss have sharedMemory
    if(this->memory->attach())
    {
        this->memory->detach();
    }
    QString fileName=QFileDialog::getOpenFileName(this,"Open Image: ",QString(),tr("Image(*.png,*.jpeg,*,bmg,*.jpg)"));

    QImage image;
    if(!image.load(fileName))
    {
        QMessageBox::information(this,"Error Message: ","Image load failed");
        return ;
    }
    //Qbuffer是文件读写的界面,但是文件是在内存中的
    QBuffer buff;
    bool ok=buff.open(QIODevice::ReadWrite);
    if(ok)
    {
        QDataStream in(&buff);
        in<<image;
    }
    else
    {
        QMessageBox::information(this,"Error Message","open buff failed");
        return ;
    }
}

void MainWindow::on_MemoryButton_clicked()
{

}
