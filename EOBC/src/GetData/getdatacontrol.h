#ifndef GETDATACONTROL_H
#define GETDATACONTROL_H

#include <QMap>
#include "facility.h"

/// @todo remove these
class StorageRead;
class SendRequestForData;
class SendDataResponse;

class GetDataControl : public QObject
{
    Q_OBJECT
public:
    GetDataControl();

    void requestAllFacilities();
    const QMap<ID, QString>& getAllFacilities() const;

    void requestFacilitiesPatients();
    const QMap<ID, QLinkedList<Patient> >& getFacilitiesPatients() const;

    void requestAreasWaitingList();
    const QMap<ID, QLinkedList<Patient> >& getAreasWaitingList() const;

    void requestFacilitiesCurrentBedNumbers();
    const QMap<ID, QLinkedList<int> >& getFacilitiesCurrentBedNumbers() const;

    void requestFacilitiesMinimumBedNumbers();
    const QMap<ID, QLinkedList<int> >& getFacilitiesMinimumBedNumbers() const;

signals:
    void receivedAllFacilities();
    void receivedFacilitiesPatients();
    void receivedAreasWaitingList();
    void receivedFacilitiesCurrentBedNumbers();
    void receivedFacilitiesMinimumBedNumbers();

public slots:
    void _receivedAllFacilities();
    void _receivedFacilitiesPatients();
    void _receivedAreasWaitingList();
    void _receivedFacilitiesCurrentBedNumbers();
    void _receivedFacilitiesMinimumBedNumbers();

private:
    QMap<ID, QString>                   _facilities;
    QMap<ID, QLinkedList<Patient> >     _facilitiesPatients;
    QMap<ID, QLinkedList<Patient> >     _areasWaitingList;
    QMap<ID, QLinkedList<int> >         _facilitiesCurrentBedNumbers;
    QMap<ID, QLinkedList<int> >         _facilitiesMinimumBedNumbers;


    /// @todo decide if these interface functions should each be in their own class
    /// to prevent classes from having abilities they shouldn't
    QString sendRequestForData(QString& args);
    QString requestData(QString& args);

    StorageRead* _storage;
    SendRequestForData* _sendRequest;
    SendDataResponse* _sendResponse;
};

#endif // GETDATACONTROL_H
