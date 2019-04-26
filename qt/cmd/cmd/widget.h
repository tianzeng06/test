#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
#include <QtDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_ComfirmButton_clicked();
    void on_CancleButton_clicked();
    void setButtonEable(const QString &qs);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
