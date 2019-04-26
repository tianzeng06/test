#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QtDebug>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_clearButton_clicked();
    void on_showDirButton_clicked();
    void singleClickedSlot(QListWidgetItem *lwt);
    void doubleClickedSlot(QListWidgetItem *lwt);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
