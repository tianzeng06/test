#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //new file
    this->setWindowTitle("new file");
    QObject::connect(ui->actionnew_N,SIGNAL(triggered()),this,SLOT(newFileSlots()));

    //open file
    QObject::connect(ui->actionopen_O,SIGNAL(triggered()),this,SLOT(openFileSlots()));

    //save file
    QObject::connect(ui->actionsave_S,SIGNAL(triggered()),this,SLOT(saveFileSlots()));

    //save as file
    QObject::connect(ui->actionsave_as_SA,SIGNAL(triggered()),this,SLOT(saveAsFileSlots()));
    //quit
    QObject::connect(ui->actionexit_E,SIGNAL(triggered()),this,SLOT(close()));
    //copy
    QObject::connect(ui->actioncopy_c,SIGNAL(triggered()),ui->textEdit,SLOT(copy()));
    //paste
    QObject::connect(ui->actionpaste_v,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));
    //selectAll
    QObject::connect(ui->actionselect,SIGNAL(triggered()),ui->textEdit,SLOT(selectAll()));
    //cut
    QObject::connect(ui->actioncut,SIGNAL(triggered()),ui->textEdit,SLOT(cut()));
    //font
    QObject::connect(ui->actionfont,SIGNAL(triggered()),this,SLOT(setFontSlots()));
    //color
    QObject::connect(ui->actioncolor,SIGNAL(triggered()),this,SLOT(setColorSlots()));
    //date
    QObject::connect(ui->actiondate_D,SIGNAL(triggered()),this,SLOT(currDateTimeSlots()));
    //about qt
    QObject::connect(ui->actionabout_qt_a,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    //about us
    QObject::connect(ui->actionabout_us_AA,SIGNAL(triggered()),this,SLOT(openWebsiteSlots()));
    //about soft
    QObject::connect(ui->actionabout_soft_AS,SIGNAL(triggered()),this,SLOT(abotSoftSlots()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //event->ignore();
    //default
    //event->accept();
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();//inherit QDialog
        switch (ret)
        {
            case QMessageBox::Save:
                // Save was clicked
                this->saveFileSlots();
                break;
            case QMessageBox::Discard:
                // Don't Save was clicked
                event->accept();
                break;
            case QMessageBox::Cancel:
                // Cancel was clicked
                event->ignore();
                break;
            default:
                // should never be reached
                break;
          }
    }
    else
    {
        event->accept();
    }
}
void MainWindow::newFileSlots()
{
    if(ui->textEdit->document()->isModified())
    {
        qDebug()<<"file modifiy";
        QMessageBox::information(this,"changed","file modifyed");
    }
    else
    {
        ui->textEdit->clear();
        this->setWindowTitle("my file");
    }
}

void MainWindow::openFileSlots()
{
    //get file name
    //QString fileName=QFileDialog::getOpenFileName(this,"open file",QDir::currentPath());
    QString fileName=QFileDialog::getOpenFileName(this,"open file","/home");// open dir
    //qDebug()<<"file name: "<<fileName;//absolute path
    if(fileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","please select text file");
        return;
    }
    else
    {
        QFile *file=new QFile(fileName);
        //or user file->setFileName(),but QFile not have arguemnt
        //qDebug()<<file->fileName();
        bool ok=file->open(QIODevice::ReadOnly);
        if(ok)
        {
            QTextStream in(file);
            ui->textEdit->setText(in.readAll());
            file->close();
            //qt Garbage Recycling Mechanism only for Graphical
            delete file;
        }
        else
        {
            QMessageBox::information(this,"Message Error","File Open Error"+file->errorString());
            return ;
        }
    }
    return;
}

void MainWindow::saveAsFileSlots()
{
    QString filename=QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
    if(filename.isEmpty())
    {
        QMessageBox::information(this,"Error Message","Please input file name");
        return ;
    }

    QFile *file=new QFile(filename);
    bool ok=file->open(QIODevice::ReadOnly);
    if(ok)
    {
        QTextStream out(file);
        out<<ui->textEdit->toPlainText();
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Message Error","File Save Error"+file->errorString());
        return ;
    }
    return ;
}

void MainWindow::saveFileSlots()
{
    if(saveFileName.isEmpty())
    {
        this->saveAsFileSlots();
    }
    else
    {
        QFile *file=new QFile(saveFileName);
        bool ok=file->open(QIODevice::ReadOnly);
        if(ok)
        {
            QTextStream out(file);
            out<<ui->textEdit->toPlainText();
            file->close();
            delete file;
        }
        else
        {
            QMessageBox::information(this,"Message Error","File Save Error"+file->errorString());
            return ;
        }
        return ;
    }
}

void MainWindow::printFlieSlots()
{
    //see QPrintDialog static member
}

void MainWindow::setFontSlots()
{
    bool ok=false;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else
    {
        QMessageBox::information(this,"Error Message","set font error");
    }
    return;
}

void MainWindow::setColorSlots()
{
    QColor color=QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
    else
    {
        QMessageBox::information(this,"Message Error","can't not use color");
    }
    return ;
}

void MainWindow::currDateTimeSlots()
{
    QDateTime datatime=QDateTime::currentDateTime();
    QString time=datatime.toString("yyyy-M-dd hh:mm:ss");
    ui->textEdit->append(time);
}

void MainWindow::openWebsiteSlots()
{
    QDesktopServices::openUrl(QUrl("http://www.baidu.com"));
}

void MainWindow::abotSoftSlots()
{
    About *about=new About();
    about->show();//unmodal dailog
    //dailog.exec()
}
