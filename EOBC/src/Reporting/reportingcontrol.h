#ifndef REPORTINGCONTROL_H
#define REPORTINGCONTROL_H

#include <QObject>
#include "generatereportwindow.h"
#include "viewallreportswindow.h"
#include "report.h"
#include "reportbars.h"
#include "viewreportwindow.h"
#include "getdatareportinginterface.h"

 /** @brief The ReportingControl class manages all forms to do with generating and viewing a report, along with the slots and signals that will be received between them
   * It contains a QVector of all the reports that have been generated since the EOBC system started.
   * all the slots and signals are connected to GetData, that will either give the forms facilities, or will be queried for a report.
   */

class ReportingControl : public QObject
{
    Q_OBJECT
public:
    explicit ReportingControl(GetDataReportingInterface& inter,QObject *parent = 0);
    ~ReportingControl();
    void run();

private:
    GenerateReportWindow rWind;
    ViewAllReportsWindow vWind;
    QVector<Report*> reports;
    QMap<ID,QString> facils;
    GetDataReportingInterface& _inter;
    bool openGenerateReport;
signals:
    void sendReportRequest(QDate, QDate, ID, QString);
public slots:
    void showGenerateReportWindow();
    void showViewAllReportsWindow();
    void reportGenerated(Report*);
    void pressedSelect(int);
    void receiveReport(QDate, QDate, ID,QPair<QString,QLinkedList<int> >& data,QPair<QString,QLinkedList<int> >& data2);
    void sendReportRequestSlot(QDate, QDate, ID, QString);
    void receivedAllFacilitiesSlot(const QMap<ID, QString> & data);

};

#endif // REPORTINGCONTROL_H
