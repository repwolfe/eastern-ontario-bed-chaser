#ifndef REPORTINGCONTROL_H
#define REPORTINGCONTROL_H

#include <QObject>
#include "generatereportwindow.h"
#include "viewallreportswindow.h"

class ReportingControl : public QObject
{
    Q_OBJECT
public:
    explicit ReportingControl(QObject *parent = 0);
    void run();
private:
    GenerateReportWindow rWind;
    ViewAllReportsWindow vWind;
signals:

public slots:
    void showGenerateReportWindow();
    void showViewAllReportsWindow();

};

#endif // REPORTINGCONTROL_H
