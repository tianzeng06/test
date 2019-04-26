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
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *ageLabel;
    QLineEdit *ageLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *socreLabel;
    QLineEdit *socreLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *gradeLabel;
    QLineEdit *gradeLineEdit;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *showButton;
    QPushButton *addButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(660, 589);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        idLabel = new QLabel(centralWidget);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));

        horizontalLayout->addWidget(idLabel);

        idLineEdit = new QLineEdit(centralWidget);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));

        horizontalLayout->addWidget(idLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        nameLabel = new QLabel(centralWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        horizontalLayout_2->addWidget(nameLabel);

        nameLineEdit = new QLineEdit(centralWidget);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        horizontalLayout_2->addWidget(nameLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        ageLabel = new QLabel(centralWidget);
        ageLabel->setObjectName(QString::fromUtf8("ageLabel"));

        horizontalLayout_3->addWidget(ageLabel);

        ageLineEdit = new QLineEdit(centralWidget);
        ageLineEdit->setObjectName(QString::fromUtf8("ageLineEdit"));

        horizontalLayout_3->addWidget(ageLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        socreLabel = new QLabel(centralWidget);
        socreLabel->setObjectName(QString::fromUtf8("socreLabel"));

        horizontalLayout_4->addWidget(socreLabel);

        socreLineEdit = new QLineEdit(centralWidget);
        socreLineEdit->setObjectName(QString::fromUtf8("socreLineEdit"));

        horizontalLayout_4->addWidget(socreLineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        gradeLabel = new QLabel(centralWidget);
        gradeLabel->setObjectName(QString::fromUtf8("gradeLabel"));

        horizontalLayout_5->addWidget(gradeLabel);

        gradeLineEdit = new QLineEdit(centralWidget);
        gradeLineEdit->setObjectName(QString::fromUtf8("gradeLineEdit"));

        horizontalLayout_5->addWidget(gradeLineEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(168, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        showButton = new QPushButton(centralWidget);
        showButton->setObjectName(QString::fromUtf8("showButton"));

        horizontalLayout_6->addWidget(showButton);

        addButton = new QPushButton(centralWidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        horizontalLayout_6->addWidget(addButton);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 660, 28));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        idLabel->setText(QApplication::translate("MainWindow", "id:", nullptr));
        nameLabel->setText(QApplication::translate("MainWindow", "name:", nullptr));
        ageLabel->setText(QApplication::translate("MainWindow", "age", nullptr));
        socreLabel->setText(QApplication::translate("MainWindow", "socre", nullptr));
        gradeLabel->setText(QApplication::translate("MainWindow", "grade", nullptr));
        showButton->setText(QApplication::translate("MainWindow", "show", nullptr));
        addButton->setText(QApplication::translate("MainWindow", "add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
