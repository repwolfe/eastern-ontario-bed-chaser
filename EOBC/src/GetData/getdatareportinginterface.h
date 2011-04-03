#ifndef GETDATAREPORTINGINTERFACE_H
#define GETDATAREPORTINGINTERFACE_H

#include <QObject>
#include "getdatacontrol.h"

/**
 * @brief Interface between the GetData and Reporting subsystems
 *
 * @todo Description
 *
 * @todo traceability
 */
class GetDataReportingInterface : public QObject
{
    Q_OBJECT
public:
    explicit GetDataReportingInterface(GetDataControl& getData);

    void requestReport(QDate fromDate, QDate toDate, ID facId, QString constraints);

signals:
    void receivedAllFacilities(const QMap<ID, QString>& data);
    void receivedReport(QDate, QDate, ID,QPair<QString,QLinkedList<int> >&,QPair<QString,QLinkedList<int> >&);

public slots:
    void _receivedAllFacilities(const QMap<ID, QString>& data);
    void _receivedReport(QDate start, QDate end, ID facId,QPair<QString,QLinkedList<int> >& data,QPair<QString,QLinkedList<int> >& data2);

private:
    GetDataControl& _getData;

};

#endif // GETDATAREPORTINGINTERFACE_H
