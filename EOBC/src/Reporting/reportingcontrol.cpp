#include "reportingcontrol.h"

ReportingControl::ReportingControl(GetDataReportingInterface& inter,QObject *parent) :
    QObject(parent), rWind() ,vWind()
{
    Q_UNUSED(inter);
    connect(&rWind,SIGNAL(reportGenerated(Report*)),this,SLOT(reportGenerated(Report*)));
    connect(&vWind,SIGNAL(pressedSelect(int)),this,SLOT(pressedSelect(int)));
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
    //QVector<ReportBars*> bars;
    //Report* r = new Report(bars);
    //reports.push_back(r);
}
void ReportingControl::reportGenerated(Report* r)
{
    reports.push_back(r);
    vWind.addItem(r);
}
void ReportingControl::pressedSelect(int index)
{
    ViewReportWindow* wind = new ViewReportWindow(reports.at(index));
    wind->show();
}
