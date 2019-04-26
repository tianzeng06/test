#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->calPushButton,SIGNAL(clicked()),this,SLOT(calSlots()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calSlots()
{
    int first=ui->firstLineEdit->text().toInt();
    int second=ui->secondLineEdit->text().toInt();
    int res=0;
    if(isdigit(first)||isdigit(second))
    {
        QMessageBox::warning(this,"Error Message","input number error");
        qDebug()<<"input error";
        return ;
    }

    int index=ui->comboBox->currentIndex();
    if(index==0)
        res=first+second;
    else if(index==1)
        res=first-second;
    else if (index==2)
        res=first*second;
    else if(index==3)
    {
        if(second==0)
        {
            //emit signal
            QMessageBox::warning(this,"Error Message","second not zero");
            qDebug()<<"sencod is zero";
            return ;
        }
        res=first/second;
    }
    ui->resultLineEdit->setText(QString::number(res));

    return ;
}
