/********************************************************************************
** Form generated from reading UI file 'updatewaitinglist.ui'
**
** Created: Tue Feb 8 20:49:19 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEWAITINGLIST_H
#define UI_UPDATEWAITINGLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UpdateWaitingList
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *closeButton;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label_3;
    QLineEdit *lineEdit_5;
    QLabel *label_6;
    QLineEdit *lineEdit_6;

    void setupUi(QDialog *UpdateWaitingList)
    {
        if (UpdateWaitingList->objectName().isEmpty())
            UpdateWaitingList->setObjectName(QString::fromUtf8("UpdateWaitingList"));
        UpdateWaitingList->resize(423, 329);
        label = new QLabel(UpdateWaitingList);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 121, 17));
        pushButton = new QPushButton(UpdateWaitingList);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 260, 111, 27));
        closeButton = new QPushButton(UpdateWaitingList);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(170, 260, 111, 27));
        lineEdit = new QLineEdit(UpdateWaitingList);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 110, 131, 27));
        label_2 = new QLabel(UpdateWaitingList);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 170, 121, 17));
        lineEdit_2 = new QLineEdit(UpdateWaitingList);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(20, 190, 131, 27));
        label_4 = new QLabel(UpdateWaitingList);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 90, 121, 17));
        lineEdit_3 = new QLineEdit(UpdateWaitingList);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(170, 110, 131, 27));
        label_5 = new QLabel(UpdateWaitingList);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(170, 90, 121, 17));
        lineEdit_4 = new QLineEdit(UpdateWaitingList);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(170, 190, 131, 27));
        label_3 = new QLabel(UpdateWaitingList);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(170, 170, 121, 17));
        lineEdit_5 = new QLineEdit(UpdateWaitingList);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(20, 30, 131, 27));
        label_6 = new QLabel(UpdateWaitingList);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(170, 10, 121, 17));
        lineEdit_6 = new QLineEdit(UpdateWaitingList);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(170, 30, 131, 27));

        retranslateUi(UpdateWaitingList);

        QMetaObject::connectSlotsByName(UpdateWaitingList);
    } // setupUi

    void retranslateUi(QDialog *UpdateWaitingList)
    {
        UpdateWaitingList->setWindowTitle(QApplication::translate("UpdateWaitingList", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UpdateWaitingList", "User Name", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("UpdateWaitingList", "Submit", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("UpdateWaitingList", "Cancel", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("UpdateWaitingList", "Privilege Level", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("UpdateWaitingList", "First Name", 0, QApplication::UnicodeUTF8));
        lineEdit_3->setText(QString());
        label_5->setText(QApplication::translate("UpdateWaitingList", " Last Name", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("UpdateWaitingList", "Facility", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("UpdateWaitingList", "Password", 0, QApplication::UnicodeUTF8));
        lineEdit_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UpdateWaitingList: public Ui_UpdateWaitingList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEWAITINGLIST_H
