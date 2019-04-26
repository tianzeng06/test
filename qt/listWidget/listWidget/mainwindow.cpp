#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setViewMode(QListWidget::IconMode);
    QObject::connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_addButton_clicked()));
    QObject::connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(singleClickedSlot(QListWidgetItem *)));
    QObject::connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(doubleClickedSlot(QListWidgetItem *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    QString cityName=ui->lineEdit->text();
    QListWidgetItem *lit=new QListWidgetItem;
    lit->setText(cityName);
    ui->listWidget->addItem(lit);
    ui->lineEdit->clear();
}

void MainWindow::on_deleteButton_clicked()
{
    QListWidgetItem *lit=ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete  lit;
}

void MainWindow::on_clearButton_clicked()
{
    /*qDebug()<<ui->listWidget->count();
    for(int i=0;i<=ui->listWidget->count();++i)
    {
        QListWidgetItem *lit=ui->listWidget->takeItem(i);
        delete  lit;
    }*/

    while(true)
    {
        QListWidgetItem *lit=ui->listWidget->takeItem(0);
        if(lit!=nullptr)
            delete  lit;
        else {
            break;
        }
    }
    return ;
}

void MainWindow::on_showDirButton_clicked()
{
    ui->listWidget->clear();
    QDir dir=QDir::currentPath();
    //QStringList fileName=QFileDialog::getOpenFileNames(this,"Open File",QDir::currentPath());
    QStringList fileName=dir.entryList();
    if(fileName.size()==0)//. ..
    {
        QMessageBox::information(this,"Message Error","Nof File Select");
        return ;
    }

    for(int i=0;i<fileName.size();++i)
    {
        if(fileName.at(i)=="."||fileName.at(i)=="..")
            continue;

        QListWidgetItem *lwt=new QListWidgetItem;
        lwt->setText(fileName.at(i));
        ui->listWidget->addItem(lwt);
    }
    return ;
}

void MainWindow::singleClickedSlot(QListWidgetItem *lwt)
{
    QMessageBox::information(this,"Info: ","single clicked text is: "+lwt->text());
    return ;
}

void MainWindow::doubleClickedSlot(QListWidgetItem *lwt)
{
    QMessageBox::information(this,"Information: ","double clicked text is: "+lwt->text());
    return ;
}
