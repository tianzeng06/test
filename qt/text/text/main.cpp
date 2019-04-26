#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap("timg.jpeg");
    QSplashScreen splash(pixmap);
    splash.show();

    for(long i=0;i<=8000000;++i);

    MainWindow w;
    w.show();
    splash.finish(&w);
    //uic(user interface complier) can transformation ui_mainwindow.h to c++ source
    return a.exec();
}
