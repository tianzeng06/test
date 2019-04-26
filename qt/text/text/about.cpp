#include "about.h"
#include "ui_about.h"

//Independent from the main window
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->movie=new QMovie("/home/ctz/work/qt/text/text/timg.gif");
    qDebug()<<"gif: "<<this->movie->frameCount();
    ui->aboutLable->setMovie(this->movie);
    this->movie->start();

    QObject::connect(ui->fearPushButton,SIGNAL(clicked()),this,SLOT(stopMovieSlot()));
    QObject::connect(ui->notafraiedPushButton,SIGNAL(clicked()),this,SLOT(startpMovieSlot()));
}

About::~About()
{
    delete ui;
}

void About::startMovieSlot()
{
    this->movie->start();
}
void About::stopMovieSlot()
{
    this->movie->stop();
}
