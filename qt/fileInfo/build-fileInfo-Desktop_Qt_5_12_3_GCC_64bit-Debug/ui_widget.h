/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *fileSizeLabel;
    QLineEdit *fileSizeLineEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *fileCreateTlabel;
    QLineEdit *fileCreateTlineEdit;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lastVisitLabel;
    QLineEdit *lastVisitLineEdit;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *isDirLabel;
    QLineEdit *isDirLineEdit;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *openFilePushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *exitLushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(660, 360);
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(1, 40, 458, 287));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        fileSizeLabel = new QLabel(widget);
        fileSizeLabel->setObjectName(QString::fromUtf8("fileSizeLabel"));

        horizontalLayout->addWidget(fileSizeLabel);

        fileSizeLineEdit = new QLineEdit(widget);
        fileSizeLineEdit->setObjectName(QString::fromUtf8("fileSizeLineEdit"));

        horizontalLayout->addWidget(fileSizeLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        fileCreateTlabel = new QLabel(widget);
        fileCreateTlabel->setObjectName(QString::fromUtf8("fileCreateTlabel"));

        horizontalLayout_2->addWidget(fileCreateTlabel);

        fileCreateTlineEdit = new QLineEdit(widget);
        fileCreateTlineEdit->setObjectName(QString::fromUtf8("fileCreateTlineEdit"));

        horizontalLayout_2->addWidget(fileCreateTlineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lastVisitLabel = new QLabel(widget);
        lastVisitLabel->setObjectName(QString::fromUtf8("lastVisitLabel"));

        horizontalLayout_3->addWidget(lastVisitLabel);

        lastVisitLineEdit = new QLineEdit(widget);
        lastVisitLineEdit->setObjectName(QString::fromUtf8("lastVisitLineEdit"));

        horizontalLayout_3->addWidget(lastVisitLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        isDirLabel = new QLabel(widget);
        isDirLabel->setObjectName(QString::fromUtf8("isDirLabel"));

        horizontalLayout_4->addWidget(isDirLabel);

        isDirLineEdit = new QLineEdit(widget);
        isDirLineEdit->setObjectName(QString::fromUtf8("isDirLineEdit"));

        horizontalLayout_4->addWidget(isDirLineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_4 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        openFilePushButton = new QPushButton(widget);
        openFilePushButton->setObjectName(QString::fromUtf8("openFilePushButton"));

        horizontalLayout_5->addWidget(openFilePushButton);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        exitLushButton = new QPushButton(widget);
        exitLushButton->setObjectName(QString::fromUtf8("exitLushButton"));

        horizontalLayout_5->addWidget(exitLushButton);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(Widget);
        QObject::connect(exitLushButton, SIGNAL(clicked()), Widget, SLOT(close()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        fileSizeLabel->setText(QApplication::translate("Widget", "fileSize:", nullptr));
        fileCreateTlabel->setText(QApplication::translate("Widget", "fileCreateT:", nullptr));
        lastVisitLabel->setText(QApplication::translate("Widget", "lastVisit:", nullptr));
        isDirLabel->setText(QApplication::translate("Widget", "isDir:", nullptr));
        openFilePushButton->setText(QApplication::translate("Widget", "openFIle", nullptr));
        exitLushButton->setText(QApplication::translate("Widget", "exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
