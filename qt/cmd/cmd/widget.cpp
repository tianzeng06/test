#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setMaximumSize(360,130);
    this->setMinimumSize(360,130);
    ui->ComfirmButton->setEnabled(false);

    //confirm
    QObject::connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_ComfirmButton_clicked()));
    //cnacle
    QObject::connect(ui->CancleButton,SIGNAL(clicked()),this,SLOT(on_CancleButton_clicked()));

    QObject::connect(ui->lineEdit,SIGNAL(textEdited(QString)),this,SLOT(setButtonEable(QString)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ComfirmButton_clicked()
{
    /*
       QProcess *myProcess = new QProcess(parent);
       myProcess->start(program, arguments);
     */
    this->setWindowTitle("my process");
    QObject *parent;
    QProcess *process=new QProcess(parent);
    process->start(ui->lineEdit->text().trimmed());
    if(!process->waitForStarted())
    {
        //emilt a error signal
        qDebug()<<"start process failed";
        return ;
    }
    ui->lineEdit->clear();
    this->close();
}

void Widget::on_CancleButton_clicked()
{
    this->close();
}

void Widget::setButtonEable(const QString &qs)
{
    ui->ComfirmButton->setEnabled(true);
}
