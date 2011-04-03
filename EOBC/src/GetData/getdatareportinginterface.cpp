#include "getdatareportinginterface.h"

GetDataReportingInterface::GetDataReportingInterface(GetDataControl &getData) :
    _getData(getData)
{
    connect (&_getData, SIGNAL(receivedAllFacilities(const QMap<ID,QString>&)), SLOT(_receivedAllFacilities(const QMap<ID,QString>&)));
    connect(&_getData, SIGNAL(receivedReport(QDate,QDate,ID,QPair<QString,QLinkedList<int> >&,QPair<QString,QLinkedList<int> >&)),
	    SLOT(_receivedReport(QDate,QDate,ID,QPair<QString,QLinkedList<int> >&,QPair<QString,QLinkedList<int> >&)));
}

void GetDataReportingInterface::requestReport(QDate fromDate, QDate toDate, ID facId, QString constraints)
{
    _getData.requestReport(fromDate, toDate, facId, constraints);
}

void GetDataReportingInterface::_receivedAllFacilities(const QMap<ID, QString>& data)
{
    emit receivedAllFacilities(data);
}

void GetDataReportingInterface::_receivedReport(QDate start, QDate end, ID facId, QPair<QString, QLinkedList<int> > &data, QPair<QString, QLinkedList<int> > &data2)
{
    emit receivedReport(start, end, facId, data, data2);
}
