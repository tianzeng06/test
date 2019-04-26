#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QDateTime>
#include <QUrl>
#include <QDesktopServices>
#include <QCloseEvent>//当程序需要关闭的时候,所处理的内容;所有的事件都是受保护的成员函数(protected)
#include <QSplashScreen>
#include <QPixmap>
#include <cstdio>
#include <cstdlib>
#include <ctime>
//#include <QTest>
#include "about.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QString saveFileName;
private slots:
    void newFileSlots();
    void openFileSlots();
    void saveAsFileSlots();
    void saveFileSlots();
    void printFlieSlots();
    void setFontSlots();
    void setColorSlots();
    void currDateTimeSlots();
    void openWebsiteSlots();
    void abotSoftSlots();
};

#endif // MAINWINDOW_H
