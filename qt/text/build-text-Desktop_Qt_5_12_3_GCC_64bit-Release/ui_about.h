/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QLabel *label;
    QPushButton *fearPushButton;
    QPushButton *notafraiedPushButton;
    QLabel *aboutLable;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(678, 431);
        label = new QLabel(About);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 10, 551, 71));
        fearPushButton = new QPushButton(About);
        fearPushButton->setObjectName(QString::fromUtf8("fearPushButton"));
        fearPushButton->setGeometry(QRect(70, 360, 89, 25));
        notafraiedPushButton = new QPushButton(About);
        notafraiedPushButton->setObjectName(QString::fromUtf8("notafraiedPushButton"));
        notafraiedPushButton->setGeometry(QRect(470, 360, 89, 25));
        aboutLable = new QLabel(About);
        aboutLable->setObjectName(QString::fromUtf8("aboutLable"));
        aboutLable->setGeometry(QRect(70, 80, 491, 251));

        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "Dialog", nullptr));
        label->setText(QApplication::translate("About", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600; text-decoration: underline; color:#ef2929;\">Copyright ownership, piracy must be investigated</span></p><p align=\"center\"><span style=\" font-weight:600; text-decoration: underline; color:#ef2929;\">the final right of interpretation belongs to their own.</span></p></body></html>", nullptr));
        fearPushButton->setText(QApplication::translate("About", "fear", nullptr));
        notafraiedPushButton->setText(QApplication::translate("About", "Not afraided", nullptr));
        aboutLable->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
