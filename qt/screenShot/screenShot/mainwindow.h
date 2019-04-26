#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QClipboard>
#include <QFileDialog>
#include <QPixmap>
#include <QDesktopWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QProcess>
#include <QDesktopServices>
//location
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
    void contextMenuEvent(QContextMenuEvent *mentEvent);

private slots:
    void on_exitButton_clicked();

    void on_newButton_clicked();

    void on_saveButton_clicked();

    void screenShotSlot();

    void startProcessSlot();
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QPixmap pixmap;
};

#endif // MAINWINDOW_H
