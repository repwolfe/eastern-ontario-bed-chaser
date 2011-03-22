#include "area.h"

/**
 * Simplest constructor for Area. Empty facility list and waiting list
 *
 * @param areaId the Area's unique ID
 */
Area::Area(ID areaId)
    : _id(areaId)
{
}

/**
 * Constructor for Area. Empty waiting list
 *
 * @param areaId the Area's unique ID
 * @param facilities the list of facilities for this Area
 */
Area::Area(ID areaId, FacilityList& facilities)
    : _id(areaId), _facilities(facilities)
{

}

/**
 * Constructor for Area. Empty facilities list
 *
 * @param areaId the Area's unique ID
 * @param waitingList the waiting list for this Area
 */
Area::Area(ID areaId, WaitingList& waitingList)
    : _id(areaId), _waitingList(waitingList)
{

}

/**
 * Constructor for Area
 *
 * @param areaId the Area's unique ID
 * @param facilities the list of facilitiets for this Area
 * @param waitingList the waiting list for this Area
 */
Area::Area(ID areaId, FacilityList& facilities, WaitingList& waitingList)
    : _id(areaId), _facilities(facilities), _waitingList(waitingList)
{

}

/**
 * Destructor for Area
 */
Area::~Area()
{
    _deleteFacilities();
    _deleteWaitingList();
}

/**
 * Add a Facility to this Area
 *
 * @param inFacility the Facility to add
 *
 * @return True if it worked, False if this Facility is already in the Area
 */
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

/**
 * Delete a Facility from the Area
 *
 * @param key of the Facility to delete
 *
 * @return True if it worked, False if this Facility doesn't exist
 */
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

/**
 * Replaces the list of Facilities for an Area with a new one.
 * Deletes the old list of Facilities
 *
 * @param inFacilities the new facilities list
 *
 */
void Area::setFacilities(FacilityList& inFacilities)
{
    if (_facilities != inFacilities)
    {
        _deleteFacilities();
        _facilities = inFacilities;
    }
}

/**
 * Returns the Facility with the given ID
 *
 * @param key of the Facility to return
 *
 * @return Facility requested, NULL if it doesn't exist
 */
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

/**
 * Add a patient to the waiting list
 *
 * @param patient the Patient to add
 *
 * @return True if it worked, False if this Patient is already in the WaitingList
 */
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

/**
 * Remove a Patient from the waiting list
 *
 * @param healthCardNum of the Patient to remove
 *
 * @return True if it worked, False if the patient doesn't exist
 */
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

/**
 * Set the WaitingList to be a new one.
 * Deletes the Patient objects from the old WaitingList
 *
 * @param inWaitingList the new waiting list
 */
void Area::setWaitingList(WaitingList& inWaitingList)
{
    if (_waitingList != inWaitingList)
    {
        _deleteWaitingList();
        _waitingList = inWaitingList;
    }
}

/**
 * Returns the WaitingList
 *
 * @return the WaitingList
 */
WaitingList& Area::getWaitingList()
{
    return _waitingList;
}

/**
 * Private function to delete all the Facility objects
 */
void Area::_deleteFacilities()
{
    foreach(Facility* facility, _facilities)
    {
        delete facility;
    }
    _facilities.clear();
}

/**
 * Private function to delete all the Patient objects
 */
void Area::_deleteWaitingList()
{
    foreach(Patient* patient, _waitingList)
    {
        delete patient;
    }
    _waitingList.clear();
}

/**
 * Return the ID of this Area
 *
 * @return ID of this Area
 */
ID Area::getAreaId() const
{
    return _id;
}

/**
 * Set the ID of this Area to be a new ID
 *
 * @param inId the new ID of this Area
 */
void Area::setAreaId(ID inId)
{
    _id = inId;
}
