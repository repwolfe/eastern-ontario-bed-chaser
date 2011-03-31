#ifndef GETDATACHANGEDATAINTERFACE_H
#define GETDATACHANGEDATAINTERFACE_H

#include <QLinkedList>
#include <QMap>

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
    const QLinkedList<QString>& getAllFacilities() const;

    void requestFacilitiesPatients();
    const QMap<QString, Patient>& getFacilitiesPatients() const;

    void requestFacilitiesWaitingList();
    const QMap<QString, QLinkedList<Patient> >& getFacilitiesWaitingList() const;

    void requestFacilitiesCurrentBedNumbers();
    const QMap<QString, QLinkedList<int> >& getFacilitiesCurrentBedNumbers() const;

    void requestFacilitiesMinimumBedNumbers();
    const QMap<QString, QLinkedList<int> >& getFacilitiesMinimumBedNumbers() const;

signals:
    void receivedAllFacilities();
    void receivedFacilitiesPatients();
    void receivedFacilitiesWaitingList();
    void receivedFacilitiesCurrentBedNumbers();
    void receivedFacilitiesMinimumBedNumbers();

public slots:
    void _receivedAllFacilities();
    void _receivedFacilitiesPatients();
    void _receivedFacilitiesWaitingList();
    void _receivedFacilitiesCurrentBedNumbers();
    void _receivedFacilitiesMinimumBedNumbers();

private:
    GetDataControl& _getData;

    QLinkedList<QString>                    _facilities;
    QMap<QString, Patient>                  _facilitiesPatients;
    QMap<QString, QLinkedList<Patient> >    _facilitiesWaitingList;
    QMap<QString, QLinkedList<int> >        _facilitiesCurrentBedNumbers;
    QMap<QString, QLinkedList<int> >        _facilitiesMinimumBedNumbers;
};

#endif // GETDATACHANGEDATAINTERFACE_H
