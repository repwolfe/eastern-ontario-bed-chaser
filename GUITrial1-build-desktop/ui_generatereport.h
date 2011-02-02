/********************************************************************************
** Form generated from reading UI file 'generatereport.ui'
**
** Created: Wed Feb 2 15:54:24 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEREPORT_H
#define UI_GENERATEREPORT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_GenerateReport
{
public:
    QPushButton *closeButton;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QTextEdit *textEdit;
    QLabel *label_3;

    void setupUi(QDialog *GenerateReport)
    {
        if (GenerateReport->objectName().isEmpty())
            GenerateReport->setObjectName(QString::fromUtf8("GenerateReport"));
        GenerateReport->resize(400, 300);
        closeButton = new QPushButton(GenerateReport);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(30, 240, 98, 27));
        label = new QLabel(GenerateReport);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 201, 17));
        lineEdit = new QLineEdit(GenerateReport);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 40, 113, 27));
        lineEdit_2 = new QLineEdit(GenerateReport);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(180, 40, 113, 27));
        label_2 = new QLabel(GenerateReport);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(180, 20, 201, 17));
        pushButton_2 = new QPushButton(GenerateReport);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 200, 98, 27));
        textEdit = new QTextEdit(GenerateReport);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(30, 100, 261, 78));
        label_3 = new QLabel(GenerateReport);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 80, 81, 17));

        retranslateUi(GenerateReport);

        QMetaObject::connectSlotsByName(GenerateReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateReport)
    {
        GenerateReport->setWindowTitle(QApplication::translate("GenerateReport", "Dialog", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("GenerateReport", "Cancel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GenerateReport", "Facility", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QString());
        label_2->setText(QApplication::translate("GenerateReport", "Date(s)", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("GenerateReport", "Submit", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("GenerateReport", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GenerateReport", "Constraints", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GenerateReport: public Ui_GenerateReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEREPORT_H
