#ifndef GETDATACONTROL_H
#define GETDATACONTROL_H

#include <QMap>
#include <QVector>
#include "facility.h"

/// @todo remove these
class StorageRead;
class SendRequestForData;
class SendDataResponse;

/**
 * @brief Handles passing data from the database to subsystems
 *
 * Takes requests from any subsystem for data and passes it via
 * signals. Interfaces take this class and the signals and pass
 * the data to the needed subsystem, making no subsystem know
 * about this class, and subsequently the database.
 *
 * This class is in the Getdata subsystem described in D2.
 */
class GetDataControl : public QObject
{
    Q_OBJECT
public:
    GetDataControl();

    void requestAllFacilities();
    void requestAllAreas();
    void requestFacilitiesPatients();
    void requestAreasWaitingList();
    void requestFacilitiesCurrentBedNumbers();
    void requestFacilitiesMinimumBedNumbers();
    void requestReport(QDate fromDate, QDate toDate, ID facId, QString constraints);

signals:
    void receivedAllFacilities(const QMap<ID, QString>&);
    void receivedAllAreas(const QMap<ID, QString>&);
    void receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient*> >&);
    void receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >&);
    void receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> >&);
    void receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> >&);

    void receivedUpdatedFacility(Facility*);
    void receivedUpdatedWaitingList(ID, WaitingList&);

    void receivedReport(QDate, QDate, ID,QPair<QString,QLinkedList<int> >&,QPair<QString,QLinkedList<int> >&);

private slots:
    void _receivedAllFacilities(const QMap<ID, QString>& data);
    void _receivedAllAreas(const QMap<ID, QString>& data);
    void _receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient*> >& data);
    void _receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >& data);
    void _receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> >& data);
    void _receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> >& data);

    void _receivedUpdatedFacility(Facility* fac);
    void _receivedUpdatedWaitingList(ID id, WaitingList& wl);

    void _receivedReport(QDate start, QDate end, ID facId,QPair<QString,QLinkedList<int> >& data,QPair<QString,QLinkedList<int> >& data2);

private:
    StorageRead* _storage;
    SendRequestForData* _sendRequest;
    SendDataResponse* _sendResponse;
};

#endif // GETDATACONTROL_H
