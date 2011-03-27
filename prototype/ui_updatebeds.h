/********************************************************************************
** Form generated from reading UI file 'updatebeds.ui'
**
** Created: Sun Mar 27 12:58:36 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEBEDS_H
#define UI_UPDATEBEDS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_UpdateBeds
{
public:
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QLabel *label;
    QPushButton *pushButton_2;
    QTextEdit *textEdit_2;
    QLabel *label_2;
    QPushButton *closeButton;

    void setupUi(QDialog *UpdateBeds)
    {
        if (UpdateBeds->objectName().isEmpty())
            UpdateBeds->setObjectName(QString::fromUtf8("UpdateBeds"));
        UpdateBeds->resize(618, 435);
        pushButton = new QPushButton(UpdateBeds);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(210, 40, 98, 27));
        textEdit = new QTextEdit(UpdateBeds);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(30, 40, 161, 31));
        label = new QLabel(UpdateBeds);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 181, 17));
        pushButton_2 = new QPushButton(UpdateBeds);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(210, 140, 98, 27));
        textEdit_2 = new QTextEdit(UpdateBeds);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(30, 140, 161, 31));
        label_2 = new QLabel(UpdateBeds);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 110, 181, 17));
        closeButton = new QPushButton(UpdateBeds);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(130, 230, 98, 27));

        retranslateUi(UpdateBeds);

        QMetaObject::connectSlotsByName(UpdateBeds);
    } // setupUi

    void retranslateUi(QDialog *UpdateBeds)
    {
        UpdateBeds->setWindowTitle(QApplication::translate("UpdateBeds", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("UpdateBeds", "Update", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UpdateBeds", "Complex Continuing Care", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("UpdateBeds", "Update", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("UpdateBeds", "Acute Care", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("UpdateBeds", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UpdateBeds: public Ui_UpdateBeds {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEBEDS_H
