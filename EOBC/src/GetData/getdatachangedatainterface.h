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
    GetDataControl& _getData;

    QMap<ID, QString>                   _facilities;
    QMap<ID, QLinkedList<Patient> >     _facilitiesPatients;
    QMap<ID, QLinkedList<Patient> >     _areasWaitingList;
    QMap<ID, QLinkedList<int> >         _facilitiesCurrentBedNumbers;
    QMap<ID, QLinkedList<int> >         _facilitiesMinimumBedNumbers;
};

#endif // GETDATACHANGEDATAINTERFACE_H
