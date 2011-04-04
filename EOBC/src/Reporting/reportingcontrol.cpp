#include "reportingcontrol.h"
#include "QPair"

ReportingControl::ReportingControl(GetDataReportingInterface& inter ,QObject *parent) :
    QObject(parent), _inter(inter)
{
    connect(&rWind,SIGNAL(reportGenerated(Report*)),this,SLOT(reportGenerated(Report*)));
    connect(&vWind,SIGNAL(pressedSelect(int)),this,SLOT(pressedSelect(int)));
    connect(&rWind,SIGNAL(sendReportRequest(QDate,QDate,ID,QString)),this,SLOT(sendReportRequestSlot(QDate,QDate,ID,QString)));

    ////INTERFACE CONNECTING
    //connect(this,SIGNAL(sendReportRequest(QDate,QDate,ID,QString)),&inter,SLOT())
    connect(&inter,SIGNAL(receivedAllFacilities(const QMap<ID,QString>&)),this,SLOT(receivedAllFacilitiesSlot(const QMap<ID,QString>&)));
    connect(&inter,SIGNAL(receivedReport(QDate,QDate,ID,QPair<QString,QLinkedList<int> >&,QPair<QString,
                                         QLinkedList<int> >&)),this,SLOT(receiveReport(QDate,QDate,ID,QPair<QString,QLinkedList<int> >&,QPair<QString,QLinkedList<int> >&)));
    openGenerateReport = false;
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
   // _inter.re
    openGenerateReport = true;
    _inter.requestAllFacilities();

   // _inter.requestReport();
    //will emit a signal to get all facilities, once received, the window will pop up
}
void ReportingControl::showViewAllReportsWindow()
{
    vWind.show();
}
void ReportingControl::receiveReport(QDate start, QDate end, ID facId,QPair<QString,QLinkedList<int> >& data,QPair<QString,QLinkedList<int> >& data2)
{
    QVector<ReportBars*> bars;
    int barnum = 0;
    int dateType = 0;
    if(end.month() - start.month() == 0)
    {
        barnum= end.day() - start.day();
    }
    else if(end.year() - start.year() == 0)
    {
       barnum= end.month() - start.month();
       dateType = 1;
    }
    else
    {
       barnum= end.year() - start.year();
       dateType = 2;
    }
    QLinkedList<int>::iterator iterData1 = data.second.begin();
    QLinkedList<int>::iterator iterData2 = data2.second.begin();
    int lastData1 = 0,lastData2 = 0;

    for(int i=0;i<data.second.count();i++)
    {
        int* barHeights = new int[4];
        if(i==0)
        {
            lastData1 = *iterData1;
            lastData2 = *iterData2;
            barHeights[0]=lastData1;
            barHeights[1]=lastData2;
            barHeights[2]=0;//rand()%(11+i)+10;
            barHeights[3]=0;//100-(barHeights[0]+barHeights[1]+barHeights[2]);
        }
        else
        {
            lastData1 += *iterData1;
            lastData2 += *iterData2;
            if(lastData1<0)
                lastData1 = 0;
            if(lastData2<0)
                lastData2 = 0;
            barHeights[0]=lastData1;
            barHeights[1]=lastData2;
            barHeights[2]=0;//rand()%(11+i)+10;
            barHeights[3]=0;//100-(barHeights[0]+barHeights[1]+barHeights[2]);
        }

        QString* barTypes = new QString[4];

        barTypes[0]="CCC";
        barTypes[1]="AC";
        barTypes[2]="CCC Open";
        barTypes[3]="AC Open";

        bars.push_back(new ReportBars(barHeights,barTypes));
        iterData2++;
        iterData1++;
    }
    QVector<QString> facilName;
    facilName.push_back(facils.value(facId));

    Report* rep = new Report(start.toString("MMMM dd yyyy") + "-"+end.toString("MMMM dd yyyy"),start,bars,(int)Convenience::HOSPITAL,dateType,facilName);
    reportGenerated(rep);

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
void ReportingControl::sendReportRequestSlot(QDate start, QDate end, ID id, QString constraints)
{
    //emit sendReportRequest(start,end,id,constraints);
    _inter.requestReport(start,end,id,constraints);
}
void ReportingControl::receivedAllFacilitiesSlot(const QMap<ID, QString>& data)
{
   // __facils = new QMap<ID, QString>();
    facils = data;
    rWind.updateFacilities(&data);
    if(this->openGenerateReport)
    {
        rWind.show();
        this->openGenerateReport = false;
    }
}

//
///SIGNALS
//
