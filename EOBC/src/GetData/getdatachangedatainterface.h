#ifndef GETDATACHANGEDATAINTERFACE_H
#define GETDATACHANGEDATAINTERFACE_H

#include "getdatacontrol.h"

/**
 * @brief Interface between the GetData and ChangeData subsystems
 *
 * Provides data needed by ChangeData forms to the subsystem without
 * revealing the internals of the database
 *
 * @todo traceability
 */
class GetDataChangeDataInterface : public QObject
{
    Q_OBJECT
public:
    explicit GetDataChangeDataInterface(GetDataControl& getData);

    void requestAllFacilityPointers();
    void requestAllAreaPointers();
    void requestFacilitiesPatients();
    void requestAreasWaitingList();
    void requestFacilitiesCurrentBedNumbers();
    void requestFacilitiesMinimumBedNumbers();
    void requestFacilityWithID(ID id);

signals:
    void receivedAllFacilityPointers(const QMap<ID, Facility*>&);
    void receivedAllAreaPointers(const QMap<ID, Area*>&);
    void receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient*> >&);
    void receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >&);
    void receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> >&);
    void receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> >&);
    void receivedFacilityWithID(Facility*);

private slots:
    void _receivedAllFacilityPointers(const QMap<ID, Facility*>& data);
    void _receivedAllAreaPointers(const QMap<ID, Area*>&);
    void _receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient*> >& data);
    void _receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >& data);
    void _receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> >& data);
    void _receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> >& data);
    void _receivedFacilityWithID(Facility* fac);

private:
    GetDataControl& _getData;
};

#endif // GETDATACHANGEDATAINTERFACE_H
