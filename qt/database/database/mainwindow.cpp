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

void MainWindow::on_showButton_clicked()
{
    //qDebug()<<QCoreApplication::libraryPaths ();
    //qDebug()<<QSqlDatabase::drivers();
    //QCoreApplication::addLibraryPath("/opt/Qt5.12.3/Tools/QtCreator/lib/Qt/plugins/sqldrivers/");
    ui->textEdit->clear();
    this->db=QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("root");
    this->db.setDatabaseName("test");
    bool ok=db.open();
    if(ok)
    {
        qDebug()<<"success open database";
    }
    else
    {
        qDebug()<<"error open database."<<this->db.lastError().text();
        return;
    }

    QSqlQuery query;
    ok=query.exec("select * from stu");
    //qDebug()<<query.lastError();
    //qDebug()<<ok;
    while(query.next())
    {
        QVariant s_id=query.value(0);
        QVariant s_name=query.value(1).toString();
        QVariant s_age=query.value(2);
        QVariant s_socre=query.value(3);
        QVariant s_grade=query.value(4);
        //qDebug()<<s_id<<" "<<s_name<<" "<<s_age<<" "<<s_socre<<" "<<s_grade;
        ui->textEdit->append(s_id.toString());
        ui->textEdit->append(s_name.toString());
        ui->textEdit->append(s_age.toString());
        ui->textEdit->append(s_socre.toString());
        ui->textEdit->append(s_grade.toString());
        ui->textEdit->append("---------------------");
    }
    db.close();
    return ;
}

void MainWindow::on_addButton_clicked()
{
    this->db=QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("root");
    this->db.setDatabaseName("test");
    if(this->db.open())
    {
        qDebug()<<"success open database";
    }
    else
    {
        qDebug()<<"error open database."<<this->db.lastError().text();
        return ;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO stu (s_id,s_name,s_age,s_socre,s_grade)"
                       "VALUES (:s_id, :s_name, :s_age,:s_socre,:s_grade)");
    qDebug()<<ui->idLineEdit->text();
    query.bindValue(":s_id",ui->idLineEdit->text());
    query.bindValue(":s_name", ui->nameLineEdit->text());
    query.bindValue(":s_age", ui->ageLineEdit->text());
    query.bindValue(":s_socre",ui->socreLineEdit->text());
    query.bindValue(":s_grade",ui->gradeLineEdit->text());
    bool ok=query.exec();
    if(!ok)
        qDebug()<<query.lastError();
    else {
        qDebug()<<"insert success";
        ui->nameLineEdit->clear();
        ui->idLineEdit->clear();
        ui->ageLineEdit->clear();
        ui->socreLineEdit->clear();
        ui->gradeLineEdit->clear();
    }
    return;
}
