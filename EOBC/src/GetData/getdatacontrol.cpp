#include "getdatacontrol.h"

GetDataControl::GetDataControl()
{
}

/**
 * @todo complete this function
 */
QString GetDataControl::sendRequestForData(QString& args)
{
    return QString(args);
}

/**
 * @todo complete this function
 */
QString GetDataControl::requestData(QString& args)
{
    return QString(args);
}

void GetDataControl::requestAllFacilities()
{
    _facilities.clear();
    /// @todo ask storage for all facilities
}

const QMap<ID, QString>&
        GetDataControl::getAllFacilities() const
{
    return _facilities;
}

void GetDataControl::requestFacilitiesPatients()
{
    _facilitiesPatients.clear();
    /// @todo ask storage for all facilities' patients
}

const QMap<ID, QLinkedList<Patient> >&
        GetDataControl::getFacilitiesPatients() const
{
    return _facilitiesPatients;
}

void GetDataControl::requestAreasWaitingList()
{
    _areasWaitingList.clear();
    /// @todo ask storage for all facilities' waiting list
}

const QMap<ID, QLinkedList<Patient> >&
        GetDataControl::getAreasWaitingList() const
{
    return _areasWaitingList;
}

void GetDataControl::requestFacilitiesCurrentBedNumbers()
{
    _facilitiesCurrentBedNumbers.clear();
    /// @todo ask all facilities' for their current bed numbers
}

const QMap<ID, QLinkedList<int> >&
        GetDataControl::getFacilitiesCurrentBedNumbers() const
{
    return _facilitiesCurrentBedNumbers;
}

void GetDataControl::requestFacilitiesMinimumBedNumbers()
{
    _facilitiesMinimumBedNumbers.clear();
    /// @todo ask all facilities' for their minimum bed numbers
}

const QMap<ID, QLinkedList<int> >&
        GetDataControl::getFacilitiesMinimumBedNumbers() const
{
    return _facilitiesMinimumBedNumbers;
}

void GetDataControl::_receivedAllFacilities()
{
    emit receivedAllFacilities();
}

void GetDataControl::_receivedFacilitiesPatients()
{
    emit receivedFacilitiesPatients();
}

void GetDataControl::_receivedAreasWaitingList()
{
    emit receivedAreasWaitingList();
}

void GetDataControl::_receivedFacilitiesCurrentBedNumbers()
{
    emit receivedFacilitiesCurrentBedNumbers();
}

void GetDataControl::_receivedFacilitiesMinimumBedNumbers()
{
    emit receivedFacilitiesMinimumBedNumbers();
}

