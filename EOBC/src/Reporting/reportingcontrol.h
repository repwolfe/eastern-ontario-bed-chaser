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
signals:

public slots:
    void showGenerateReportWindow();
    void showViewAllReportsWindow();
    void reportGenerated(Report*);
    void pressedSelect(int);
    void receiveReport(QString);

};

#endif // REPORTINGCONTROL_H
