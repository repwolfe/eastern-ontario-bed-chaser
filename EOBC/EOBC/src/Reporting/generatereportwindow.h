#ifndef GENERATEREPORTWINDOW_H
#define GENERATEREPORTWINDOW_H

#include <QWidget>
#include <QtGui/qgridlayout.h>
#include <QtGui>
#include "report.h"

#include "reportbars.h"
#include <QtGui/QMessageBox>

/** @brief GenerateReportWindow is the reporting window that users can generate reports about certain facilities.
  * Holds data about all the facilities on the map, and has several signals that will give data to other classes
  * so they can generate reports.
  */

class GenerateReportWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GenerateReportWindow(QWidget *parent = 0);
    ~GenerateReportWindow();
    void updateFacilities(const QMap<ID,QString>* facils);
signals:
    ////FOR TESTING ONLY
    void reportGenerated(Report*);
    ////FOR TESTING ONLY
    void sendReportRequest(QDate, QDate, ID, QString);

public slots:
    void pressedSubmit();
    void pressedCancel();
private:

private:
    QGridLayout layout;
    QDateEdit* dateStartEntry;
    QDateEdit* dateEndEntry;
    QListWidget* facilities;
    const QMap<ID,QString>* __facils;
    QMap<int,ID>* facilToRows;
    QComboBox* constraints;

};

#endif // GENERATEREPORTWINDOW_H
