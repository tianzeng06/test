#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedMemory>
#include <QFileDialog>
#include <QPixmap>
#include <QDataStream>
#include <QMessageBox>
#include <QBuffer>

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
    void on_fileButton_clicked();

    void on_MemoryButton_clicked();

private:
    Ui::MainWindow *ui;
    QSharedMemory *memory;
};

#endif // MAINWINDOW_H
