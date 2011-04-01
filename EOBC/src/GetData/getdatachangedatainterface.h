#ifndef GETDATACHANGEDATAINTERFACE_H
#define GETDATACHANGEDATAINTERFACE_H

#include "getdatacontrol.h"

/**
 * @brief Interface between the GetData and ChangeData subsystems
 *
 * @todo Description
 *
 * @todo traceability
 */
class GetDataChangeDataInterface : public QObject
{
    Q_OBJECT
public:
    explicit GetDataChangeDataInterface(GetDataControl& getData);

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

public slots:
    void _receivedAllFacilities(const QMap<ID, QString>& data);
    void _receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient*> >& data);
    void _receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >& data);
    void _receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> >& data);
    void _receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> >& data);

private:
    GetDataControl& _getData;
};

#endif // GETDATACHANGEDATAINTERFACE_H
