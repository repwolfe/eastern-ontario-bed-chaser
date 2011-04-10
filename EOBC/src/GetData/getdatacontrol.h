#ifndef GETDATACONTROL_H
#define GETDATACONTROL_H

#include <QMap>
#include <QVector>
#include "area.h"
#include "storageread.h"
#include "sendgetdatainterface.h"

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
    GetDataControl(StorageRead& sr,SendGetDataInterface& sgd);

    void requestAllFacilities();
    void requestAllFacilityPointers();
    void requestAllAreaPointers();
    void requestFacilitiesPatients();
    void requestAreasWaitingList();
    void requestFacilitiesCurrentBedNumbers();
    void requestFacilitiesMinimumBedNumbers();
    void requestReport(QDate fromDate, QDate toDate, ID facId, QString constraints);
    void requestFacilityWithID(ID id);

signals:
    void receivedAllFacilities(const QMap<ID, QString>&);
    void receivedAllFacilityPointers(const QMap<ID, Facility*>&);
    void receivedAllAreaPointers(const QMap<ID, Area*>&);
    void receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient*> >&);
    void receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >&);
    void receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> >&);
    void receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> >&);


    void sendFacilityUpdate(Facility* f);

    void receivedUpdatedFacility(Facility*f,bool remote);
    void receivedUpdatedWaitingList(ID, WaitingList&);
    void receivedFacilityWithID(Facility*);

    void receivedReport(QDate, QDate, ID,QPair<QString,QLinkedList<int> >&,QPair<QString,QLinkedList<int> >&);

private slots:
    void _receivedUpdatedFacility(Facility* fac,bool remote);
    void _receivedUpdatedWaitingList(ID id, WaitingList& wl);
    void _receivedFacilityWithID(Facility*);

    void _receivedReport(QDate start, QDate end, ID facId,QPair<QString,QLinkedList<int> >& data,QPair<QString,QLinkedList<int> >& data2);

public slots:
    void receivedFacilityRequest();
    void recievedUserAcct();

private:
    StorageRead& _storage;
    SendGetDataInterface& _sendGetDataI;
};

#endif // GETDATACONTROL_H
