#include "area.h"

/**
 * Simplest constructor for Area. Empty facility list and waiting list
 *
 * @param areaId the Area's unique ID
 */
Area::Area(ID areaId)
    : _id(areaId), _isOurArea(false)
{
}

/**
 * Constructor for Area. Empty waiting list
 *
 * @param areaId the Area's unique ID
 * @param facilities the list of facilities for this Area
 */
Area::Area(ID areaId, FacilityList& facilities)
    : _id(areaId), _facilities(facilities), _isOurArea(false)
{
    foreach (Facility* facility, facilities)
    {
	facility->setAreaThisIsIn(this);
    }
}

/**
 * Constructor for Area. Empty facilities list
 *
 * @param areaId the Area's unique ID
 * @param waitingList the waiting list for this Area
 */
Area::Area(ID areaId, WaitingList& waitingList)
    : _id(areaId), _waitingList(waitingList), _isOurArea(false)
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
    : _id(areaId), _facilities(facilities), _waitingList(waitingList), _isOurArea(false)
{
    foreach (Facility* facility, facilities)
    {
	facility->setAreaThisIsIn(this);
    }
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

    if (iter == _facilities.end())
    {
        _facilities.insert(key, inFacility);
	inFacility->setAreaThisIsIn(this);
        return true;
    }

    return false;
}

/**
 * Remove a Facility from the Area, does NOT delete it
 * Since you are passing in a pointer, its assumed you will delete it
 *
 * @param facility to remove
 *
 * @return True if it worked, False if this Facility doesn't exist
 */
bool Area::removeFacility(Facility* facility)
{
    FacilityList::iterator iter = _facilities.find(facility->getFacilityId());

    if (iter != _facilities.end())
    {
        _facilities.erase(iter);
        return true;
    }
    return false;
}

/**
 * Remove a Facility from the Area, deleting it
 *
 * @param key of the Facility to remove
 *
 * @return True if it worked, False if this Facility doesn't exist
 */
bool Area::removeFacility(ID key)
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
	foreach (Facility* facility, _facilities)
	{
	    facility->setAreaThisIsIn(this);
	}
    }
}

/**
 * Returns the Facility with the given ID
 *
 * @param key of the Facility to return
 *
 * @return Facility requested, NULL if it doesn't exist
 */
Facility* Area::getFacility(ID key)
{
    FacilityList::iterator iter = _facilities.find(key);

    if (iter != _facilities.end())
    {
        return iter.value();
    }
    else
    {
        Logger::errorMessage("Area", "getFacility()", "No Facility with ID: ", QString::number(key));
        return 0;
    }
}

/**
 * Returns all the Facility objects in this Area
 *
 * @return all the Facility objects
 */
FacilityList& Area::getFacilities()
{
    return _facilities;
}

/**
 * Add a patient to the waiting list
 *
 * @param hcn the Health Card Number of the Patient
 * @param first the Patient's first name
 * @param last the Patient's last name
 * @param placedOnWL date placed on a waiting list
 *
 * @return True if it worked, False if this Patient is already in the WaitingList
 */
bool Area::addPatientToWaitingList(QString hcn, QString first, QString last, QDate placedOnWL)
{
    WaitingList::const_iterator iter = _waitingList.find(hcn);

    if (iter == _waitingList.end())
    {
	// Only Patients requiring Long Term Care can be added to a waiting list
	// Requirement FR.PATIENTS.04
	_waitingList.insert(hcn, new Patient(hcn, first, last, EOBC::LTC, placedOnWL));
        return true;
    }

    return false;
}

/**
 * Add a patient to the waiting list
 *
 * @param patient the Patient pointer to add, takes ownership
 *
 * @return True if it worked, False if this Patient is already in the WaitingList
 */
bool Area::addPatientToWaitingList(Patient* patient)
{
    WaitingList::const_iterator iter = _waitingList.find(patient->getHealthCardNumber());

    if (iter == _waitingList.end())
    {
	_waitingList.insert(patient->getHealthCardNumber(), patient);
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
bool Area::removePatientFromWaitingList(QString healthCardNum)
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
 * Returns the WaitingList as a LinkedList
 *
 * @return the Waiting List
 */
QLinkedList<Patient*> Area::getWaitingListAsList()
{
    QLinkedList<Patient*> list;
    foreach (Patient* pat, _waitingList)
    {
	list << pat;
    }
    return list;
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

/**
 * @return True if this Area is the user of the system's Area, False otherwise
 */
bool Area::isOurArea() const
{
    return _isOurArea;
}

void Area::makeThisOurArea()
{
    _isOurArea = true;
}
