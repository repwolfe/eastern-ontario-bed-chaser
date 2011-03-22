#include "area.h"

Area::Area()
{
}

Area::Area(FacilityList& facilities)
    : _facilities(facilities)
{

}

Area::Area(WaitingList& waitingList)
    : _waitingList(waitingList)
{

}

Area::Area(FacilityList& facilities, WaitingList& waitingList)
    : _facilities(facilities), _waitingList(waitingList)
{

}

Area::~Area()
{
    _deleteFacilities();
    _deleteWaitingList();
}

bool Area::addFacility(Facility* inFacility)
{
    ID key = inFacility->getFacilityId();
    FacilityList::iterator iter = _facilities.find(key);

    if (iter != _facilities.end())
    {
        _facilities.insert(key, inFacility);
        return true;
    }

    return false;
}

bool Area::deleteFacility(ID& key)
{
    FacilityList::iterator iter = _facilities.find(key);

    if (iter != _facilities.end())
    {
        delete iter.value();
        _facilities.erase(iter);
        return true;
    }
    return false;
}

void Area::setFacilities(FacilityList& inFacilities)
{
    if (_facilities != inFacilities)
    {
        _deleteFacilities();
        _facilities = inFacilities;
    }
}

Facility* Area::getFacility(ID& key)
{
    FacilityList::iterator iter = _facilities.find(key);

    if (iter != _facilities.end())
    {
        return iter.value();
    }
    else
    {
        return 0;
    }
}

bool Area::addPatientToWaitingList(Patient* patient)
{
    QString healthCardNum = patient->getHealthCardNumber();

    WaitingList::const_iterator iter = _waitingList.find(healthCardNum);

    if (iter != _waitingList.end())
    {
        _waitingList.insert(healthCardNum, patient);
        return true;
    }

    return false;
}

bool Area::removePatientFromWaitingList(QString& healthCardNum)
{
    WaitingList::iterator iter = _waitingList.find(healthCardNum);

    if (iter != _waitingList.end())
    {
        delete iter.value();
        _waitingList.erase(iter);
        return true;
    }
    return false;
}

void Area::setWaitingList(WaitingList& inWaitingList)
{
    if (_waitingList != inWaitingList)
    {
        _deleteWaitingList();
        _waitingList = inWaitingList;
    }
}

WaitingList& Area::getWaitingList()
{
    return _waitingList;
}

void Area::_deleteFacilities()
{
    foreach(Facility* facility, _facilities)
    {
        delete facility;
    }
    _facilities.clear();
}

void Area::_deleteWaitingList()
{
    foreach(Patient* patient, _waitingList)
    {
        delete patient;
    }
    _waitingList.clear();
}
