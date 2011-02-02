/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Feb 2 15:21:50 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionBeds;
    QAction *actionExit;
    QAction *actionWaiting_List;
    QAction *actionOccupancy_Rates;
    QAction *actionMove_Patients;
    QAction *actionUser_Accounts;
    QAction *actionFacilities;
    QAction *actionGenerate_Report;
    QAction *actionView_Report;
    QAction *actionAbout_EOBC;
    QAction *actionHelp;
    QAction *actionLog_Off;
    QWidget *centralwidget;
    QLabel *mapBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *updateBedsButton;
    QPushButton *updateWaitingListButton;
    QPushButton *generateReportButton;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *logOffButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAdd;
    QMenu *menuHelp;
    QMenu *menuHelp_2;
    QMenu *menuHelp_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 700);
        actionBeds = new QAction(MainWindow);
        actionBeds->setObjectName(QString::fromUtf8("actionBeds"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionWaiting_List = new QAction(MainWindow);
        actionWaiting_List->setObjectName(QString::fromUtf8("actionWaiting_List"));
        actionOccupancy_Rates = new QAction(MainWindow);
        actionOccupancy_Rates->setObjectName(QString::fromUtf8("actionOccupancy_Rates"));
        actionMove_Patients = new QAction(MainWindow);
        actionMove_Patients->setObjectName(QString::fromUtf8("actionMove_Patients"));
        actionUser_Accounts = new QAction(MainWindow);
        actionUser_Accounts->setObjectName(QString::fromUtf8("actionUser_Accounts"));
        actionFacilities = new QAction(MainWindow);
        actionFacilities->setObjectName(QString::fromUtf8("actionFacilities"));
        actionGenerate_Report = new QAction(MainWindow);
        actionGenerate_Report->setObjectName(QString::fromUtf8("actionGenerate_Report"));
        actionView_Report = new QAction(MainWindow);
        actionView_Report->setObjectName(QString::fromUtf8("actionView_Report"));
        actionAbout_EOBC = new QAction(MainWindow);
        actionAbout_EOBC->setObjectName(QString::fromUtf8("actionAbout_EOBC"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionLog_Off = new QAction(MainWindow);
        actionLog_Off->setObjectName(QString::fromUtf8("actionLog_Off"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mapBox = new QLabel(centralwidget);
        mapBox->setObjectName(QString::fromUtf8("mapBox"));
        mapBox->setGeometry(QRect(0, 0, 1000, 1000));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(810, 200, 161, 20));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(830, 230, 141, 20));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(830, 260, 141, 20));
        label_3->setFont(font1);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(830, 290, 171, 20));
        label_4->setFont(font1);
        updateBedsButton = new QPushButton(centralwidget);
        updateBedsButton->setObjectName(QString::fromUtf8("updateBedsButton"));
        updateBedsButton->setGeometry(QRect(50, 540, 151, 27));
        updateWaitingListButton = new QPushButton(centralwidget);
        updateWaitingListButton->setObjectName(QString::fromUtf8("updateWaitingListButton"));
        updateWaitingListButton->setGeometry(QRect(240, 540, 151, 27));
        generateReportButton = new QPushButton(centralwidget);
        generateReportButton->setObjectName(QString::fromUtf8("generateReportButton"));
        generateReportButton->setGeometry(QRect(430, 540, 151, 27));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(810, 340, 171, 20));
        label_5->setFont(font);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(830, 370, 141, 20));
        label_6->setFont(font1);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(810, 420, 171, 20));
        label_7->setFont(font);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(830, 450, 141, 20));
        label_8->setFont(font1);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(810, 70, 161, 20));
        label_9->setFont(font);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(830, 100, 161, 20));
        label_10->setFont(font1);
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(810, 130, 161, 20));
        label_11->setFont(font);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(830, 160, 161, 20));
        label_12->setFont(font1);
        logOffButton = new QPushButton(centralwidget);
        logOffButton->setObjectName(QString::fromUtf8("logOffButton"));
        logOffButton->setGeometry(QRect(810, 540, 151, 27));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAdd = new QMenu(menubar);
        menuAdd->setObjectName(QString::fromUtf8("menuAdd"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuHelp_2 = new QMenu(menubar);
        menuHelp_2->setObjectName(QString::fromUtf8("menuHelp_2"));
        menuHelp_3 = new QMenu(menubar);
        menuHelp_3->setObjectName(QString::fromUtf8("menuHelp_3"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAdd->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menubar->addAction(menuHelp_2->menuAction());
        menubar->addAction(menuHelp_3->menuAction());
        menuFile->addAction(actionLog_Off);
        menuFile->addAction(actionExit);
        menuAdd->addAction(actionBeds);
        menuAdd->addAction(actionUser_Accounts);
        menuAdd->addAction(actionFacilities);
        menuHelp->addAction(actionWaiting_List);
        menuHelp->addAction(actionOccupancy_Rates);
        menuHelp->addAction(actionMove_Patients);
        menuHelp_2->addAction(actionGenerate_Report);
        menuHelp_2->addAction(actionView_Report);
        menuHelp_3->addAction(actionHelp);
        menuHelp_3->addAction(actionAbout_EOBC);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionBeds->setText(QApplication::translate("MainWindow", "Beds", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionWaiting_List->setText(QApplication::translate("MainWindow", "Waiting List", 0, QApplication::UnicodeUTF8));
        actionOccupancy_Rates->setText(QApplication::translate("MainWindow", "Occupancy Rates", 0, QApplication::UnicodeUTF8));
        actionMove_Patients->setText(QApplication::translate("MainWindow", "Move Patients", 0, QApplication::UnicodeUTF8));
        actionUser_Accounts->setText(QApplication::translate("MainWindow", "User Accounts", 0, QApplication::UnicodeUTF8));
        actionFacilities->setText(QApplication::translate("MainWindow", "Facilities", 0, QApplication::UnicodeUTF8));
        actionGenerate_Report->setText(QApplication::translate("MainWindow", "Generate Report", 0, QApplication::UnicodeUTF8));
        actionView_Report->setText(QApplication::translate("MainWindow", "View Report", 0, QApplication::UnicodeUTF8));
        actionAbout_EOBC->setText(QApplication::translate("MainWindow", "About EOBC", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        actionLog_Off->setText(QApplication::translate("MainWindow", "Log Off", 0, QApplication::UnicodeUTF8));
        mapBox->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Occupancy Rates:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "AC: 600/1200", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "CCC: 300/1200", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Open Beds: 300/1200", 0, QApplication::UnicodeUTF8));
        updateBedsButton->setText(QApplication::translate("MainWindow", " Update Beds", 0, QApplication::UnicodeUTF8));
        updateWaitingListButton->setText(QApplication::translate("MainWindow", "Update Waiting List", 0, QApplication::UnicodeUTF8));
        generateReportButton->setText(QApplication::translate("MainWindow", "Generate Report", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Coordinates:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "23.5N , 10.7W", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Waiting List:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "56 patients", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Facility Name:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Franklin Hospital", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Facility Location:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Western Ottawa", 0, QApplication::UnicodeUTF8));
        logOffButton->setText(QApplication::translate("MainWindow", "Log Off", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuAdd->setTitle(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Update", 0, QApplication::UnicodeUTF8));
        menuHelp_2->setTitle(QApplication::translate("MainWindow", "Reports", 0, QApplication::UnicodeUTF8));
        menuHelp_3->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
