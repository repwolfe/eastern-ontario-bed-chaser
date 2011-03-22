#include "facility.h"

Facility::Facility(int facilityId, int numACBeds, int numCCCBeds)
    : _facilityId(facilityId), _numACBeds(numACBeds), _numCCCBeds(numCCCBeds)
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
 * @param Patient the patient to add
 * @param Caretype which bed to add to
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
 * Adds a patient to this facility, and to a specific type of bed.
 * The facility then takes ownsership of the patient, deleting it
 * in the destructor, unless the patient is manually removed from
 * the facility.
 *
 * @param QString the patient's healthCardNumber
 * @param QString the patient's name
 * @param QDate the date the patient was placed on waiting list
 * @param QDate the date the patient was admitted to this facility
 * @param Caretype which bed to add to
 *
 * @return True if it worked, False otherwise
 */
bool Facility::addPatientToBed(QString& healthCardNumber, QString& name, QDate &placedOnWaitingList, QDate& admissionDate, CareType type)
{
    return addPatientToBed(new Patient(healthCardNumber, name, placedOnWaitingList), type);
}


/**
 * Moves a patient with a particular health card number to
 * a different bed
 *
 * @param QString healthCardNum of the patient
 * @param CareType new bed type to place the patient in
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
 * @param Patient* the patient to remove from this facility, not deleted
 * @return bool True if the patient was removed, false otherwise
 */
bool Facility::removePatient(Patient* patient)
{
    PatientContainer* containedIn = 0;
    QString& healthCardNum = patient->getHealthCardNumber();
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
 * @param QString the healthCardNumber of the Patient to remove
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
 * @param QString health card number of patient being request
 * @return Patient* with given healthCardNum or NULL if it's not in the facility
 */
Patient* Facility::getPatient(QString& healthCardNum) const
{
    PatientContainer* temp;
    return _getPatient(healthCardNum, temp);
}

/**
 * Gets the Patient pointer with the given health card num, as well as which bed their in.
 *
 * @param QString health card number of patient being request
 * @param PatientContainer the container the patient is in (aka which bed their in)
 * @return Patient* with given healthCardNum or NULL if it's not in the facility
 */
Patient* Facility::_getPatient(QString& healthCardNum, PatientContainer*& outContainedIn) const
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
 * @param unsigned the num to increase by
 * @param CareType which bed to increase in number
 */
void Facility::addBeds(unsigned num, CareType type)
{
    PatientContainer* patients;
    int *numBeds;

    // Only if the correct caretype was passed in
    if (_getPointersForType(type, patients, numBeds))
    {
        *numBeds += num;
    }
    /// @todo What should happen if addBeds fails
    else
    {

    }
}

/**
 * Decreases the number of beds this facility has
 * of a particular type
 *
 * @param unsigned the num to decrease by
 * @param CareType which bed to decrease in number
 */
void Facility::decreaseBeds(unsigned num, CareType type)
{
    PatientContainer* patients;
    int *numBeds;
    if (!_getPointersForType(type, patients, numBeds))
    {
        /// @todo What to do if wrong care type was passed
    }

    if (*numBeds - (int)num < patients->size())
    {
        /// @todo What to do if decreaseBeds fails
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
}

/**
 * Return the number of beds of a particular type
 *
 * @param CareType which bed type to check
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

/**
 * Returns this facility's id
 *
 * @return the facility's id number
 */
int Facility::getFacilityId() const
{
    return _facilityId;
}

/**
 * Internal function used to get pointers of the
 * containers and bed numbers for a particular caretype
 *
 * @param CareType which type to get pointers for
 * @param PatientContainer out pointer to the container of this caretype
 * @param int out pointer to the number of beds of this caretype
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
