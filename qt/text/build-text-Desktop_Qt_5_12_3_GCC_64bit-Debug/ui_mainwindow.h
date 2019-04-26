/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionnew_N;
    QAction *actionopen_O;
    QAction *actionsave_S;
    QAction *actionprint_P;
    QAction *actionsave_as_SA;
    QAction *actionexit_E;
    QAction *actiondate_D;
    QAction *actioncopy_c;
    QAction *actionpaste_v;
    QAction *actionselect;
    QAction *actioncut;
    QAction *actionfont;
    QAction *actioncolor;
    QAction *actionabout_qt_a;
    QAction *actionabout_us_AA;
    QAction *actionabout_soft_AS;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menufile_F;
    QMenu *menuedit_E;
    QMenu *menucolor;
    QMenu *menuhelp_H;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(793, 413);
        actionnew_N = new QAction(MainWindow);
        actionnew_N->setObjectName(QString::fromUtf8("actionnew_N"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/images/timg (1).jpeg"), QSize(), QIcon::Normal, QIcon::Off);
        actionnew_N->setIcon(icon);
        actionopen_O = new QAction(MainWindow);
        actionopen_O->setObjectName(QString::fromUtf8("actionopen_O"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/images/u=3533882817,4081823563&fm=26&gp=0.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionopen_O->setIcon(icon1);
        actionsave_S = new QAction(MainWindow);
        actionsave_S->setObjectName(QString::fromUtf8("actionsave_S"));
        actionprint_P = new QAction(MainWindow);
        actionprint_P->setObjectName(QString::fromUtf8("actionprint_P"));
        actionsave_as_SA = new QAction(MainWindow);
        actionsave_as_SA->setObjectName(QString::fromUtf8("actionsave_as_SA"));
        actionexit_E = new QAction(MainWindow);
        actionexit_E->setObjectName(QString::fromUtf8("actionexit_E"));
        actiondate_D = new QAction(MainWindow);
        actiondate_D->setObjectName(QString::fromUtf8("actiondate_D"));
        actioncopy_c = new QAction(MainWindow);
        actioncopy_c->setObjectName(QString::fromUtf8("actioncopy_c"));
        actionpaste_v = new QAction(MainWindow);
        actionpaste_v->setObjectName(QString::fromUtf8("actionpaste_v"));
        actionselect = new QAction(MainWindow);
        actionselect->setObjectName(QString::fromUtf8("actionselect"));
        actioncut = new QAction(MainWindow);
        actioncut->setObjectName(QString::fromUtf8("actioncut"));
        actionfont = new QAction(MainWindow);
        actionfont->setObjectName(QString::fromUtf8("actionfont"));
        actioncolor = new QAction(MainWindow);
        actioncolor->setObjectName(QString::fromUtf8("actioncolor"));
        actionabout_qt_a = new QAction(MainWindow);
        actionabout_qt_a->setObjectName(QString::fromUtf8("actionabout_qt_a"));
        actionabout_us_AA = new QAction(MainWindow);
        actionabout_us_AA->setObjectName(QString::fromUtf8("actionabout_us_AA"));
        actionabout_soft_AS = new QAction(MainWindow);
        actionabout_soft_AS->setObjectName(QString::fromUtf8("actionabout_soft_AS"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setStyleSheet(QString::fromUtf8("\n"
"	background-image: url(:/new/prefix1/images/timg.jpeg);\n"
"	font: 57 11pt \"Ubuntu\";"));

        verticalLayout->addWidget(textEdit);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 793, 28));
        menufile_F = new QMenu(menuBar);
        menufile_F->setObjectName(QString::fromUtf8("menufile_F"));
        menuedit_E = new QMenu(menuBar);
        menuedit_E->setObjectName(QString::fromUtf8("menuedit_E"));
        menucolor = new QMenu(menuBar);
        menucolor->setObjectName(QString::fromUtf8("menucolor"));
        menuhelp_H = new QMenu(menuBar);
        menuhelp_H->setObjectName(QString::fromUtf8("menuhelp_H"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menufile_F->menuAction());
        menuBar->addAction(menuedit_E->menuAction());
        menuBar->addAction(menucolor->menuAction());
        menuBar->addAction(menuhelp_H->menuAction());
        menufile_F->addAction(actionnew_N);
        menufile_F->addAction(actionopen_O);
        menufile_F->addAction(actionsave_S);
        menufile_F->addAction(actionsave_as_SA);
        menufile_F->addSeparator();
        menufile_F->addAction(actionprint_P);
        menufile_F->addAction(actionexit_E);
        menuedit_E->addAction(actionselect);
        menuedit_E->addAction(actioncopy_c);
        menuedit_E->addAction(actioncut);
        menuedit_E->addAction(actionpaste_v);
        menuedit_E->addSeparator();
        menuedit_E->addAction(actiondate_D);
        menucolor->addAction(actionfont);
        menucolor->addAction(actioncolor);
        menuhelp_H->addAction(actionabout_qt_a);
        menuhelp_H->addAction(actionabout_us_AA);
        menuhelp_H->addAction(actionabout_soft_AS);
        mainToolBar->addAction(actionnew_N);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionopen_O);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionnew_N->setText(QApplication::translate("MainWindow", "new(&N)", nullptr));
        actionopen_O->setText(QApplication::translate("MainWindow", "open(&O)", nullptr));
        actionsave_S->setText(QApplication::translate("MainWindow", "save(&S)", nullptr));
        actionprint_P->setText(QApplication::translate("MainWindow", "print(&P)", nullptr));
        actionsave_as_SA->setText(QApplication::translate("MainWindow", "save as(&SA)", nullptr));
        actionexit_E->setText(QApplication::translate("MainWindow", "exit", nullptr));
        actiondate_D->setText(QApplication::translate("MainWindow", "date(&D)", nullptr));
        actioncopy_c->setText(QApplication::translate("MainWindow", "copy(&c)", nullptr));
        actionpaste_v->setText(QApplication::translate("MainWindow", "paste(&v)", nullptr));
        actionselect->setText(QApplication::translate("MainWindow", "select", nullptr));
        actioncut->setText(QApplication::translate("MainWindow", "cut", nullptr));
        actionfont->setText(QApplication::translate("MainWindow", "font", nullptr));
        actioncolor->setText(QApplication::translate("MainWindow", "color", nullptr));
        actionabout_qt_a->setText(QApplication::translate("MainWindow", "about qt(&a)", nullptr));
        actionabout_us_AA->setText(QApplication::translate("MainWindow", "about us(&AA)", nullptr));
        actionabout_soft_AS->setText(QApplication::translate("MainWindow", "about soft(&AS)", nullptr));
        menufile_F->setTitle(QApplication::translate("MainWindow", "file(&F)", nullptr));
        menuedit_E->setTitle(QApplication::translate("MainWindow", "edit(&E)", nullptr));
        menucolor->setTitle(QApplication::translate("MainWindow", "sytle", nullptr));
        menuhelp_H->setTitle(QApplication::translate("MainWindow", "help(&H)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
