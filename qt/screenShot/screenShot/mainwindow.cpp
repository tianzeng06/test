#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->saveButton,SIGNAL(clicked()),SLOT(on_saveButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
     this->close();
}
void MainWindow::screenShotSlot()
{
    this->pixmap=QPixmap::grabWindow(QApplication::desktop()->winId());
    ui->screenShotLabel->setPixmap(this->pixmap.scaled(ui->screenShotLabel->size()));
    QClipboard *board=QApplication::clipboard();
    //QString origanText=board->text();
    //qDebug()<<origanText;
    board->setPixmap(this->pixmap);

    this->show();
    this->timer->stop();
}

void MainWindow::on_newButton_clicked()
{
    if(ui->isDeslayCheckBox->isChecked())
    {
        this->hide();//this->show();
        this->timer=new QTimer;
        QObject::connect(this->timer,SIGNAL(timeout()),SLOT(screenShotSlot()));
        //this->timer->start(ui->spinBox->value()*1000);
        this->timer->start(1000/24);
    }
    else
    {
        qApp->beep();//beng
    }
    return ;
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this,"save file",QDir::homePath());
    this->pixmap.save(fileName);

}

void MainWindow::contextMenuEvent(QContextMenuEvent *mentEvent)
{
    QMenu *menu=new QMenu(this);
    QAction *action=new QAction(this);
    QAction *startProcess=new QAction(this);
    QObject::connect(startProcess,SIGNAL(triggered()),this,SLOT(startProcess));
    QObject::connect(action,SIGNAL(triggered()),this,SLOT(on_saveButton_clicked()));
    action->setText("Save As");
    startProcess->setText("start process");
    menu->addAction(action);
    menu->addSeparator();
    menu->addAction(startProcess);
    menu->exec(QCursor::pos());

    return ;
}

void MainWindow::startProcessSlot()
{
    QProcess *process=new QProcess;
    process->start("cmd");
}
