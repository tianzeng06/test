#include "widget.h"
#include <QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    int res=a.exec();
    qDebug()<<"qDebug exec return is :"<<res<<endl;
    return 0;
}
