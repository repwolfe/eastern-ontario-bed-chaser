#ifndef REPORTINGCONTROL_H
#define REPORTINGCONTROL_H

#include <QObject>
#include "generatereportwindow.h"
#include "viewallreportswindow.h"
#include "report.h"
#include "reportbars.h"
#include "viewreportwindow.h"
#include "getdatareportinginterface.h"

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
    QMap<ID,QString>* __facils;
signals:
    void sendReportRequest(QDate, QDate, ID, QString);
public slots:
    void showGenerateReportWindow();
    void showViewAllReportsWindow();
    void reportGenerated(Report*);
    void pressedSelect(int);
    void receiveReport(QDate, QDate, ID,QPair<QString,QLinkedList<int> >& data,QPair<QString,QLinkedList<int> >& data2);
    void sendReportRequestSlot(QDate, QDate, ID, QString);
    void receivedAllFacilitiesSlot(QMap<ID, QString> & data);

};

#endif // REPORTINGCONTROL_H
