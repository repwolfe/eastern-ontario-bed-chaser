#ifndef GETDATACONTROL_H
#define GETDATACONTROL_H

#include <QMap>
#include <QVector>
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
    void requestFacilitiesPatients();
    void requestAreasWaitingList();
    void requestFacilitiesCurrentBedNumbers();
    void requestFacilitiesMinimumBedNumbers();

signals:
    void receivedAllFacilities(const QMap<ID, QString>&);
    void receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient*> >&);
    void receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >&);
    void receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> >&);
    void receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> >&);

private slots:
    void _receivedAllFacilities(const QMap<ID, QString>& data);
    void _receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient*> >& data);
    void _receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >& data);
    void _receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> >& data);
    void _receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> >& data);

private:
    /// @todo decide if these interface functions should each be in their own class
    /// to prevent classes from having abilities they shouldn't
    QString sendRequestForData(QString& args);
    QString requestData(QString& args);

    StorageRead* _storage;
    SendRequestForData* _sendRequest;
    SendDataResponse* _sendResponse;
};

#endif // GETDATACONTROL_H
