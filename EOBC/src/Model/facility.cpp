#include "facility.h"
#include "area.h"
#include <stdlib.h>

Facility::Facility(ID facilityId, QString facilityName, int numACBeds, int numCCCBeds, int numLTCBeds, QPoint location)
    : _facilityId(facilityId), _facilityName(facilityName)
    , _numACBeds(numACBeds), _numCCCBeds(numCCCBeds), _numLTCBeds(numLTCBeds)
    , _location(location), _ourFacility(false)
{
    // No LTC Beds but possibly AC or CCC, make it a Normal facility
    if (numACBeds >= 0 && numCCCBeds >= 0 && numLTCBeds == 0)
    {
        _type = Facility::Normal;
        _patients.push_back(&_patientsAC);
        _patients.push_back(&_patientsCCC);
    }
    // Only LTC Beds make LTC Facility
    else if (numACBeds == 0 && numCCCBeds == 0 && numLTCBeds > 0)
    {
        _type = Facility::LTC;
        _patients.push_back(&_patientsLTC);
    }
    else
    {
        Logger::errorMessage("Facility", "Facility()", "Incorrect bed numbers passed in, forcing Normal Facility");
        _numLTCBeds = 0;
        // Prevent negative numbers passing in
        _numACBeds = abs(_numACBeds);
        _numCCCBeds = abs(_numCCCBeds);
        _type = Facility::Normal;
        _patients.push_back(&_patientsAC);
        _patients.push_back(&_patientsCCC);
    }
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
	Logger::errorMessage("Facility", "addPatientToBed()", "Incorrect Care Type passed");
        return false;
    }

    // If there aren't any more available beds
    if (!(container->size() < *numBeds))
    {
        Logger::errorMessage("Facility", "addPatientToBed()", "No more beds of type ", QString::number(type));
        return false;
    }

    container->insert(patient->getHealthCardNumber(), patient);

    return true;
}

/**
 * Moves a patient with a particular health card number to
 * a different bed
 *
 * @param healthCardNum of the Patient
 * @param type new bed type to place the Patient in
 *
 * @return True if it worked, False otherwise
 */
bool Facility::movePatientToBed(QString healthCardNum, CareType type)
{
    Patient* patient = getPatient(healthCardNum);

    if (!patient)
    {
        Logger::errorMessage("Facility", "movePatientToBed()", "No patient with health card number ", healthCardNum);
        return false;
    }

    if (!removePatient(patient))    // Doesn't delete the pointer
    {
        return false;
    }

    return addPatientToBed(patient, type);
}

/**
 * Moves a patient with a particular health card number from this Facility
 * to another with a particular CareType
 *
 * @param healthCardNum of the Patient
 * @param otherFacility Facility to move the Patient to
 * @param type new bed type to place the Patient in
 *
 * @return True if it worked, False otherwise
 */
bool Facility::movePatientToFacility(QString healthCardNum, Facility* otherFacility, CareType type)
{
    Patient* patient = getPatient(healthCardNum);

    if (!patient)
    {
        Logger::errorMessage("Facility", "movePatientToFacility()", "No patient with health card number ", healthCardNum);
	return false;
    }

    if (!removePatient(patient))    // Doesn't delete the pointer
    {
	return false;
    }

    // Add it to the other facility
    return otherFacility->addPatientToBed(patient, type);
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
        Logger::errorMessage("Facility", "removePatient(Patient)", "This patient isn't in any bed: ", healthCardNum);
        return false;
    }

    containedIn->remove(healthCardNum);
    // Don't delete the patient

    return true;
}

/**
 * Removes an Patient from this facility, deletes the object.
 *
 * @param healthCardNumber of the Patient to remove
 * @return bool True if the patient was removed, false otherwise
 */
bool Facility::removePatient(QString healthCardNumber)
{
    PatientContainer* containedIn = 0;
    Patient* patient = _getPatient(healthCardNumber, containedIn);

    // If this patient isn't in any bed, can't remove them from the facility
    if (!patient)
    {
        Logger::errorMessage("Facility", "removePatient(QString)", "This patient isn't in any bed: ", healthCardNumber);
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
 *
 * @return Patient* with given healthCardNum or NULL if it's not in the facility
 */
Patient* Facility::getPatient(QString healthCardNumber) const
{
    PatientContainer* temp;
    return _getPatient(healthCardNumber, temp);
}

/**
 * Gets all the Patients in a particular bed
 *
 * @param type of bed to get the patients of
 *
 * @return PatientContainer* with given care type or NULL if incorrect care type
 */
PatientContainer* Facility::getPatientsForType(CareType type)
{
    PatientContainer* container = 0;
    int* temp;
    _getPointersForType(type, container, temp);
    return container;
}

/**
 * Gets all Patients in this Facility, regardless of bed type
 *
 * @return PatientContainer with all the patients
 */
PatientContainer Facility::getAllPatients()
{
    PatientContainer allPatients;
    foreach (PatientContainer* patients, _patients)
    {
	allPatients.unite(*patients);
    }
    // Pretty sure this isn't a deep copy being returned
    return allPatients;
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

    if (!patient)
    {
        Logger::errorMessage("Facility", "_getPatient()", "No patient found with healthCardNum: ", healthCardNum);
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
    if (num == 0)
    {
	return true;	// Do nothing
    }

    PatientContainer* patients;
    int *numBeds;

    // Only if the correct caretype was passed in
    if (_getPointersForType(type, patients, numBeds))
    {
        *numBeds += num;
	return true;
    }

    Logger::errorMessage("Facility", "addBeds()", "Incorrect bed type passed in: ", QString::number(type));
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
    if (num == 0)
    {
	return true;	// Do nothing
    }
    PatientContainer* patients;
    int *numBeds;
    if (!_getPointersForType(type, patients, numBeds))
    {
        Logger::errorMessage("Facility", "decreaseBeds()", "Incorrect bed type passed in: ", QString::number(type));
	return false;
    }

    if (*numBeds - (int)num < patients->size())
    {
	Logger::errorMessage("Facility", "decreaseBeds()", "Trying to remove beds containing patients");
	return false;
    }
    else if ((*numBeds - (int)num) < 0)
    {
	Logger::errorMessage("Facility", "decreaseBeds()", "Trying to remove more beds than this facility has");
	return false;
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
	// Simply return 0
        return 0;
    }

    return *numBeds;
}

/**
 * Return the number of occupied beds of a particular type
 *
 * @param type which bed type to check
 *
 * @return number of occupied beds of a particular type
 */
int Facility::getNumBedsOccupied(CareType type)
{
    PatientContainer* patientsInBeds;
    int* temp;

    // If they passed in the wrong bed type
    if (!_getPointersForType(type, patientsInBeds, temp))
    {
        Logger::errorMessage("Facility", "getNumBedsOccupied()", "Incorrect bed type passed in: ", QString::number(type));
        return 0;
    }

    return patientsInBeds->size();
}

/**
 * Return the number of available beds of a particular type
 *
 * @param type which bed type to check
 *
 * @return number of available beds of a particular type
 */
int Facility::getNumBedsAvailable(CareType type)
{
    return getNumBeds(type) - getNumBedsOccupied(type);
}

ID Facility::getFacilityId() const
{
    return _facilityId;
}

void Facility::setFacilityId(ID theId)
{
    _facilityId = theId;
}


const QString& Facility::getFacilityName() const
{
    return _facilityName;
}

void Facility::setFacilityName(QString& inFacilityName)
{
    _facilityName = inFacilityName;
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
 * @return True if this Facility is the user of the system's Facility, False otherwise
 */
bool Facility::isOurFacility() const
{
    return _ourFacility;
}

void Facility::makeThisOurFacility()
{
    _ourFacility = true;
}

Area* Facility::getAreaThisIsIn() const
{
    return __inThisArea;
}

void Facility::setAreaThisIsIn(Area* inArea)
{
    __inThisArea = inArea;
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

    if (_type == Facility::Normal)
    {
        // AC or CC should be passed in
        if (type == EOBC::AC)
        {
            container = &_patientsAC;
            numBeds = &_numACBeds;
            return true;
        }
        else if (type == EOBC::CCC)
        {
            container = &_patientsCCC;
            numBeds = &_numCCCBeds;
            return true;
        }
    }

    else if (_type == Facility::LTC)
    {
        // Only LTC should be passed in
        if (type == EOBC::LTC)
        {
            container = &_patientsLTC;
            numBeds = &_numLTCBeds;
            return true;
        }
    }
    return false;
}
