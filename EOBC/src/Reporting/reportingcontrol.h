#ifndef REPORTINGCONTROL_H
#define REPORTINGCONTROL_H

#include <QObject>
#include "generatereportwindow.h"
#include "viewallreportswindow.h"
#include "report.h"
class ReportingControl : public QObject
{
    Q_OBJECT
public:
    explicit ReportingControl(QObject *parent = 0);
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
    void receiveReport(QString);

};

#endif // REPORTINGCONTROL_H
