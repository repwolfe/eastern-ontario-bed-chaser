#include "getdatachangedatainterface.h"

GetDataChangeDataInterface::GetDataChangeDataInterface(GetDataControl &getData) :
    _getData(getData)
{
}

void GetDataChangeDataInterface::requestAllFacilities()
{
    _facilities.clear();
    /// @todo ask getData for all facilities
}

const QLinkedList<QString>&
        GetDataChangeDataInterface::getAllFacilities() const
{
    return _facilities;
}

void GetDataChangeDataInterface::requestFacilitiesPatients()
{
    _facilitiesPatients.clear();
    /// @todo ask getData for all facilities' patients
}

const QMap<QString, Patient>&
        GetDataChangeDataInterface::getFacilitiesPatients() const
{
    return _facilitiesPatients;
}

void GetDataChangeDataInterface::requestFacilitiesWaitingList()
{
    _facilitiesWaitingList.clear();
    /// @todo ask getData for all facilities' waiting list
}

const QMap<QString, QLinkedList<Patient> >&
        GetDataChangeDataInterface::getFacilitiesWaitingList() const
{
    return _facilitiesWaitingList;
}

void GetDataChangeDataInterface::requestFacilitiesCurrentBedNumbers()
{
    _facilitiesCurrentBedNumbers.clear();
    /// @todo ask all facilities' for their current bed numbers
}

const QMap<QString, QLinkedList<int> >&
        GetDataChangeDataInterface::getFacilitiesCurrentBedNumbers() const
{
    return _facilitiesCurrentBedNumbers;
}

void GetDataChangeDataInterface::requestFacilitiesMinimumBedNumbers()
{
    _facilitiesMinimumBedNumbers.clear();
    /// @todo ask all facilities' for their minimum bed numbers
}

const QMap<QString, QLinkedList<int> >&
        GetDataChangeDataInterface::getFacilitiesMinimumBedNumbers() const
{
    return _facilitiesMinimumBedNumbers;
}

void GetDataChangeDataInterface::_receivedAllFacilities()
{
    emit receivedAllFacilities();
}

void GetDataChangeDataInterface::_receivedFacilitiesPatients()
{
    emit receivedFacilitiesPatients();
}

void GetDataChangeDataInterface::_receivedFacilitiesWaitingList()
{
    emit receivedFacilitiesWaitingList();
}

void GetDataChangeDataInterface::_receivedFacilitiesCurrentBedNumbers()
{
    emit receivedFacilitiesCurrentBedNumbers();
}

void GetDataChangeDataInterface::_receivedFacilitiesMinimumBedNumbers()
{
    emit receivedFacilitiesMinimumBedNumbers();
}
