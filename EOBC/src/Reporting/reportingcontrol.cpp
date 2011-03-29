#include "reportingcontrol.h"

ReportingControl::ReportingControl(QObject *parent) :
    QObject(parent), rWind() ,vWind()
{

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
