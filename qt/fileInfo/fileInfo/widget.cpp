#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QObject::connect(ui->openFilePushButton,SIGNAL(clicked()),this,SLOT(getFileInfoSlot()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::getFileInfoSlot()
{
    QString name=QFileDialog::getOpenFileName(this,"open file",QDir::homePath());
    if(name.isEmpty())
    {
        QMessageBox::information(this,"Error Message","Please select a file");
        return ;
    }

    QFileInfo file(name);

    ui->fileSizeLineEdit->setText(QString::number(file.size()));

    //use birthData is Invalid
    QDateTime createTime=file.created();
    qDebug()<<createTime;
    ui->fileCreateTlineEdit->setText(createTime.toString("yyyy-M-dd hh:mm:ss"));

    QDateTime lastVist=file.lastRead();
    ui->lastVisitLineEdit->setText(lastVist.toString("yyyy-M-dd hh:mm:ss"));

    if(file.isDir())
        ui->isDirLineEdit->setText("Yes");
    else
        ui->isDirLineEdit->setText("No");
    return ;
}
