#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QMovie>
#include <QDebug>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private:
    Ui::About *ui;
    QMovie *movie;
private slots:
    void startMovieSlot();
    void stopMovieSlot();

};

#endif // ABOUT_H
