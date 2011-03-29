#include "reportingcontrol.h"

ReportingControl::ReportingControl(QObject *parent) :
    QObject(parent), rWind() ,vWind()
{

}
ReportingControl::~ReportingControl()
{
    QVector<Report*>::iterator iter = reports.begin();
    while(iter != reports.end())
    {
        delete *iter;
        iter++;
    }
}

void ReportingControl::run()
{

}
///
///SLOTS
///
void ReportingControl::showGenerateReportWindow()
{
    rWind.show();
}
void ReportingControl::showViewAllReportsWindow()
{
    vWind.show();
}
void ReportingControl::receiveReport(QString )
{
    QVector<int> bars;
    Report* r = new Report(bars);
    reports.push_back(r);
}
