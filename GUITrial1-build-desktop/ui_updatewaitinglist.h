/********************************************************************************
** Form generated from reading UI file 'updatewaitinglist.ui'
**
** Created: Wed Feb 2 01:31:48 2011
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
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_UpdateWaitingList
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *closeButton;
    QTextEdit *textEdit;

    void setupUi(QDialog *UpdateWaitingList)
    {
        if (UpdateWaitingList->objectName().isEmpty())
            UpdateWaitingList->setObjectName(QString::fromUtf8("UpdateWaitingList"));
        UpdateWaitingList->resize(400, 300);
        label = new QLabel(UpdateWaitingList);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 121, 17));
        pushButton = new QPushButton(UpdateWaitingList);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 200, 111, 27));
        closeButton = new QPushButton(UpdateWaitingList);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(20, 240, 111, 27));
        textEdit = new QTextEdit(UpdateWaitingList);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 50, 351, 131));

        retranslateUi(UpdateWaitingList);

        QMetaObject::connectSlotsByName(UpdateWaitingList);
    } // setupUi

    void retranslateUi(QDialog *UpdateWaitingList)
    {
        UpdateWaitingList->setWindowTitle(QApplication::translate("UpdateWaitingList", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UpdateWaitingList", "Waiting List", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("UpdateWaitingList", "Update", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("UpdateWaitingList", "Close", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("UpdateWaitingList", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Smith, John</li></ul>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Smith, John</li></ul>\n"
"<ul st"
                        "yle=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Smith, John</li></ul>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Smith, John</li></ul>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Smith, John</li></ul>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Smith, John</li></ul>\n"
""
                        "<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Smith, John</li></ul></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UpdateWaitingList: public Ui_UpdateWaitingList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEWAITINGLIST_H
