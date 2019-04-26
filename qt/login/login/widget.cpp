#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);//no password displayed
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_loginPushButton_clicked()
{
    if(ui->nameLineEdit->text()=="ctz"&&ui->pwdLineEdit->text()=="123456")
    {
        QMessageBox::information(this,"Congratulate","login sucess");
        //dosomething
    }
    else
    {
        QMessageBox::information(this,"failed","login failed");
        return;
    }
    return ;
}
