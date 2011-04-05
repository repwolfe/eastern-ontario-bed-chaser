#include "reportingcontrol.h"
#include "QPair"

/** The constructor for ReportingControl.
  * connects all the slots and signals between classes and subsystems
  * also takes in the interface between GetData and Reporting.
  * @param inter the interface between Reporting and GetData, allows for the slots and signals to be connected
  * @param parent unused
  */
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
/** the destructor for ReportingControl
  * deletes all the reports that the conrol has received since the EOBC system was started
  */
ReportingControl::~ReportingControl()
{
    QVector<Report*>::iterator iter = reports.begin();
    while(iter != reports.end())
    {
        delete *iter;
        iter++;
    }
}
 /** does nothing
   */
void ReportingControl::run()
{

}
///
///SLOTS
///
 /** showGenerateReportWindow is the slot connected to the button in GenerateReportWindow
   * once pressed, a flag is set to true that data is waiting to be received,
   * and a signal is sent to GetData so the facilities can be loaded into GenerateReportWindow
   */
void ReportingControl::showGenerateReportWindow()
{
   // _inter.re
    openGenerateReport = true;
    _inter.requestAllFacilities();

   // _inter.requestReport();
    //will emit a signal to get all facilities, once received, the window will pop up
}
 /** showViewAllReportsWindow is the slot connected to the QAction from the map
   * just shows the viewAllReports window
   */
void ReportingControl::showViewAllReportsWindow()
{
    vWind.show();
}
 /** receiveReport contains most of the intelligence in ReportingControl
   * it is a slot that gets called by GetDataControl.
   * several parameters are recieved as raw data from the remote facilities
   * the data is parsed, and a report object is made, and stored in main memory
   * @param start the date object of the start date of the data received
   * @param end the date object of the end date of the data received
   * @param facId the "integer" id of the current facility that has sent report data
   * @param data A stupidly complicated data type that contains the constraints of the data received, paired with a linked list of all data. For one kind of care only
   * @param data2 A stupidly complicated data type that contains the constraints of the data received, paired with a linked list of all data. For one kind of care only
   */
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
        QVector<QString> barTypes;
        QVector<int> barHeights;
        if(i==0)
        {
            lastData1 = *iterData1;
            lastData2 = *iterData2;
            barHeights.push_back(lastData1);
            barHeights.push_back(lastData2);
            barTypes.push_back("CCC ");
            barTypes.push_back("AC ");
            //barHeights[2]=0;//rand()%(11+i)+10;
            //barHeights[3]=0;//100-(barHeights[0]+barHeights[1]+barHeights[2]);
        }
        else
        {
            lastData1 += *iterData1;
            lastData2 += *iterData2;
            if(lastData1<0)
                lastData1 = 0;
            if(lastData2<0)
                lastData2 = 0;
            barHeights.push_back(lastData1);
            barHeights.push_back(lastData2);
            barTypes.push_back("CCC ");
            barTypes.push_back("AC ");
            //barHeights[2]=0;//rand()%(11+i)+10;
            //barHeights[3]=0;//100-(barHeights[0]+barHeights[1]+barHeights[2]);
        }






        bars.push_back(new ReportBars(barHeights,barTypes));
        iterData2++;
        iterData1++;
    }
    QVector<QString> facilName;
    facilName.push_back(facils.value(facId));

    Report* rep = new Report(start.toString("MMMM dd yyyy") + "-"+end.toString("MMMM dd yyyy"),start,bars,(int)Convenience::HOSPITAL,dateType,facilName);
    reportGenerated(rep);

}
 /** reportGenerated is a slot that is called whenever a report object has been generated.
   * it is pushed into the reports QVector, and added to the QListWidget of the ViewAllReportsWindow class
   * @param r the report that was generated
   */
void ReportingControl::reportGenerated(Report* r)
{
    reports.push_back(r);
    vWind.addItem(r);
}
/** pressedSelect is the slot that is connected to the select button in ViewAllReportsWindow
  * gives the index of the current row selected, and shows the ViewReportWindow of the report in the QVector at that row
  * @param index the current row selected in the QListWidget in ViewAllReportsWindow
  */
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

/** receivedAllFacilitiesSlot is the slot that is called when GetDataControl sends a signal to give all facilities
  * this signal is sent to other unrelated windows as well, so a flag must be set to true before the GenerateReportWindow is opened.
  * @param data the facility data sent by the GetDataControl class.
  */
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
