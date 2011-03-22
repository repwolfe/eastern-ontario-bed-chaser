#include "facility.h"

Facility::Facility(ID facilityId, int numACBeds, int numCCCBeds, QPoint& location)
    : _facilityId(facilityId)
    , _numACBeds(numACBeds), _numCCCBeds(numCCCBeds), _numLTCBeds(0)
    , _location(location)
{
    _patients.push_back(&_patientsAC);
    _patients.push_back(&_patientsCCC);
}

/**
 * Deletes all the patients in this facility
 */
Facility::~Facility()
{
    foreach (PatientContainer* container, _patients)
    {
        foreach(Patient* patient, *container)
        {
            delete patient;
        }
    }
}

/**
 * Adds a patient to this facility, and to a specific type of bed.
 * The facility then takes ownsership of the patient, deleting it
 * in the destructor, unless the patient is manually removed from
 * the facility.
 *
 * @param patient the patient to add
 * @param type which bed to add to
 *
 * @return True if it worked, False otherwise
 */
bool Facility::addPatientToBed(Patient* patient, CareType type)
{
    PatientContainer* container;
    int* numBeds;

    // If they chose an incorrect CareType
    if (!_getPointersForType(type, container, numBeds))
    {
        return false;
    }

    // If there aren't any more available beds
    if (!(container->size() < *numBeds))
    {
        return false;
    }

    container->insert(patient->getHealthCardNumber(), patient);

    return true;
}

/**
 * Moves a patient with a particular health card number to
 * a different bed
 *
 * @param healthCardNum of the patient
 * @param type new bed type to place the patient in
 *
 * @return True if it worked, False otherwise
 */
bool Facility::movePatientToBed(QString& healthCardNum, CareType type)
{
    PatientContainer* newContainer;
    PatientContainer* containedIn = 0;
    int* temp;

    // If the wrong care type was passed in
    if (!_getPointersForType(type, newContainer, temp))
    {
        return false;
    }

    Patient* patient = _getPatient(healthCardNum, containedIn);

    if (!patient)
    {
        return false;
    }

    if (!removePatient(patient))
    {
        return false;
    }

    return addPatientToBed(patient, type);
}

/**
 * Removes an Patient from this facility, does NOT delete the object.
 * Since the client is passing in the pointer, it's their job to delete it.
 *
 * @param patient the Patient to remove from this facility, not deleted
 *
 * @return True if the patient was removed, false otherwise
 */
bool Facility::removePatient(Patient* patient)
{
    PatientContainer* containedIn = 0;
    const QString& healthCardNum = patient->getHealthCardNumber();
    _getPatient(healthCardNum, containedIn);

    // If this patient isn't in any bed, can't remove them from the facility
    if (!containedIn)
    {
        return false;
    }

    containedIn->remove(healthCardNum);

    return true;
}

/**
 * Removes an Patient from this facility, deletes the object.
 *
 * @param healthCardNumber of the Patient to remove
 * @return bool True if the patient was removed, false otherwise
 */
bool Facility::removePatient(QString& healthCardNumber)
{
    PatientContainer* containedIn = 0;
    Patient* patient = _getPatient(healthCardNumber, containedIn);

    if (!patient)
    {
        return false;
    }

    containedIn->remove(healthCardNumber);
    delete patient;

    return true;
}

/**
 * Gets the Patient pointer with the given health card num.
 *
 * @param healthCardNumber of patient being request
 * @return Patient* with given healthCardNum or NULL if it's not in the facility
 */
Patient* Facility::getPatient(QString& healthCardNumber) const
{
    PatientContainer* temp;
    return _getPatient(healthCardNumber, temp);
}

/**
 * Gets the Patient pointer with the given health card num, as well as which bed their in.
 *
 * @param healthCardNum of patient being request
 * @param outContainedIn the PatientContainer the Patient is in (aka which bed their in)
 *
 * @return Patient* with given healthCardNum or NULL if it's not in the facility
 */
Patient* Facility::_getPatient(const QString& healthCardNum, PatientContainer*& outContainedIn) const
{
    Patient* patient = 0;

    // Goes through each container of patients to find them.
    // O(1) since its O(1) per find * n (n = num of bed types)
    foreach(PatientContainer* container, _patients)
    {
        PatientContainer::const_iterator iter = container->find(healthCardNum);
        if (iter != container->end())
        {
            patient = *iter;
            outContainedIn = container;
        }
    }

    return patient;
}

/**
 * Increases the number of beds this facility has
 * of a particular type
 *
 * @param num the num to increase by
 * @param type which bed to increase in number
 */
bool Facility::addBeds(unsigned num, CareType type)
{
    PatientContainer* patients;
    int *numBeds;

    // Only if the correct caretype was passed in
    if (_getPointersForType(type, patients, numBeds))
    {
        *numBeds += num;
	return true;
    }
    /// @todo What should happen if addBeds fails
    return false;
}

/**
 * Decreases the number of beds this facility has
 * of a particular type
 *
 * @param num the num to decrease by
 * @param type which bed to decrease in number
 */
bool Facility::decreaseBeds(unsigned num, CareType type)
{
    PatientContainer* patients;
    int *numBeds;
    if (!_getPointersForType(type, patients, numBeds))
    {
        /// @todo What to do if wrong care type was passed
	return false;
    }

    if (*numBeds - (int)num < patients->size())
    {
        /// @todo What to do if decreaseBeds fails
	return false;
    }
    else if ((*numBeds - (int)num) < 0)
    {
        /// @todo If too many beds decreased, go to 0?
        *numBeds = 0;
    }
    else
    {
        *numBeds -= num;
    }
    return true;
}

/**
 * Return the number of beds of a particular type
 *
 * @param type which bed type to check
 *
 * @return number of beds of a particular type
 */
int Facility::getNumBeds(CareType type)
{
    PatientContainer* temp;
    int* numBeds;

    // If they passed in the wrong bed type
    if (!_getPointersForType(type, temp, numBeds))
    {
        /// @todo make sure this is the right thing to do...maybe log error?
        return 0;
    }

    return *numBeds;
}

ID Facility::getFacilityId() const
{
    return _facilityId;
}

void Facility::setFacilityId(ID theId)
{
    _facilityId = theId;
}

const QPoint& Facility::getLocation() const
{
    return _location;
}

void Facility::setLocation(QPoint& location)
{
    _location = location;
}

/**
 * Internal function used to get pointers of the
 * containers and bed numbers for a particular caretype
 *
 * @param type which type to get pointers for
 * @param container out PatientContainer pointer to the container of this caretype
 * @param numBeds out int pointer to the number of beds of this caretype
 *
 * @return True if acceptable type passed in, False otherwise
 */
inline bool Facility::_getPointersForType(CareType type, PatientContainer* &container, int* &numBeds)
{
    container = 0;
    numBeds = 0;
    switch (type)
    {
    case AC:
        container = &_patientsAC;
        numBeds = &_numACBeds;
        break;

    case CCC:
        container = &_patientsCCC;
        numBeds = &_numCCCBeds;
        break;

    default:
        return false;
    }

    return true;
}
