#include "getdatachangedatainterface.h"

GetDataChangeDataInterface::GetDataChangeDataInterface(GetDataControl &getData) :
    _getData(getData)
{
    connect(&_getData, SIGNAL(receivedAllFacilities()), SLOT(_receivedAllFacilities()));
    connect(&_getData, SIGNAL(receivedFacilitiesCurrentBedNumbers()), SLOT(_receivedFacilitiesCurrentBedNumbers()));
    connect(&_getData, SIGNAL(receivedFacilitiesMinimumBedNumbers()), SLOT(_receivedFacilitiesMinimumBedNumbers()));
    connect(&_getData, SIGNAL(receivedFacilitiesPatients()), SLOT(_receivedFacilitiesPatients()));
    connect(&_getData, SIGNAL(receivedAreasWaitingList()), SLOT(_receivedAreasWaitingList()));
}

void GetDataChangeDataInterface::requestAllFacilities()
{
    _facilities.clear();
    _getData.requestAllFacilities();
}

const QMap<ID, QString>&
        GetDataChangeDataInterface::getAllFacilities() const
{
    return _facilities;
}

void GetDataChangeDataInterface::requestFacilitiesPatients()
{
    _facilitiesPatients.clear();
    _getData.requestFacilitiesPatients();
}

const QMap<ID, QLinkedList<Patient> >&
        GetDataChangeDataInterface::getFacilitiesPatients() const
{
    return _facilitiesPatients;
}

void GetDataChangeDataInterface::requestAreasWaitingList()
{
    _areasWaitingList.clear();
    _getData.requestAreasWaitingList();
}

const QMap<ID, QLinkedList<Patient> >&
        GetDataChangeDataInterface::getAreasWaitingList() const
{
    return _areasWaitingList;
}

void GetDataChangeDataInterface::requestFacilitiesCurrentBedNumbers()
{
    _facilitiesCurrentBedNumbers.clear();
    _getData.requestFacilitiesCurrentBedNumbers();
}

const QMap<ID, QLinkedList<int> >&
        GetDataChangeDataInterface::getFacilitiesCurrentBedNumbers() const
{
    return _facilitiesCurrentBedNumbers;
}

void GetDataChangeDataInterface::requestFacilitiesMinimumBedNumbers()
{
    _facilitiesMinimumBedNumbers.clear();
    _getData.requestFacilitiesMinimumBedNumbers();
}

const QMap<ID, QLinkedList<int> >&
        GetDataChangeDataInterface::getFacilitiesMinimumBedNumbers() const
{
    return _facilitiesMinimumBedNumbers;
}

void GetDataChangeDataInterface::_receivedAllFacilities()
{
    _facilities = _getData.getAllFacilities();
    emit receivedAllFacilities();
}

void GetDataChangeDataInterface::_receivedFacilitiesPatients()
{
    _facilitiesPatients = _getData.getFacilitiesPatients();
    emit receivedFacilitiesPatients();
}

void GetDataChangeDataInterface::_receivedAreasWaitingList()
{
    _areasWaitingList = _getData.getAreasWaitingList();
    emit receivedAreasWaitingList();
}

void GetDataChangeDataInterface::_receivedFacilitiesCurrentBedNumbers()
{
    _facilitiesCurrentBedNumbers = _getData.getFacilitiesCurrentBedNumbers();
    emit receivedFacilitiesCurrentBedNumbers();
}

void GetDataChangeDataInterface::_receivedFacilitiesMinimumBedNumbers()
{
    _facilitiesMinimumBedNumbers = _getData.getFacilitiesMinimumBedNumbers();
    emit receivedFacilitiesMinimumBedNumbers();
}
