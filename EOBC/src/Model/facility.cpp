#include "facility.h"

Facility::Facility(int numACBeds, int numCCCBeds)
    : _numACBeds(numACBeds), _numCCCBeds(numCCCBeds)
{
    _patients.push_back(&_patientsAC);
    _patients.push_back(&_patientsCCC);
    //_patients.push_back(_patientsLTC);
}
Facility::~Facility()
{

}

bool Facility::addPatientToBed(Inpatient* patient, CareType type)
{
    PatientContainer* container;
    int* numBeds;
    _getPointersForType(type, container, numBeds);

    // If there aren't any more available beds
    if (!(container->size() < *numBeds))
    {
        return false;
    }

    container->insert(patient->getHealthCardNumber(), patient);

    return true;
}

bool Facility::addPatientToBed(QString& healthCardNumber, QString& name, QDate &placedOnWaitingList, QDate& admissionDate, CareType type)
{
    return addPatientToBed(new Inpatient(healthCardNumber, name, placedOnWaitingList, admissionDate), type);
}

bool Facility::movePatientToBed(QString& healthCardNum, CareType type)
{
    PatientContainer* newContainer;
    PatientContainer* containedIn = 0;
    int* temp;
    _getPointersForType(type, newContainer, temp);
    Inpatient* patient = _getInpatient(healthCardNum, containedIn);

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
 * Removes an Inpatient from this facility, does NOT delete the object.
 * Since the client is passing in the pointer, it's their job to delete it.
 *
 * @param Inpatient* the patient to remove from this facility, not deleted
 * @return bool True if the patient was removed, false otherwise
 */
bool Facility::removePatient(Inpatient* patient)
{
    PatientContainer* containedIn = 0;
    QString& healthCardNum = patient->getHealthCardNumber();
    _getInpatient(healthCardNum, containedIn);

    // If this patient isn't in any bed, can't remove them from the facility
    if (!containedIn)
    {
        return false;
    }

    containedIn->remove(healthCardNum);

    return true;
}

/**
 * Removes an Inpatient from this facility, deletes the object.
 *
 * @param QString the healthCardNumber of the Inpatient to remove
 * @return bool True if the patient was removed, false otherwise
 */
bool Facility::removePatient(QString& healthCardNumber)
{
    PatientContainer* containedIn = 0;
    Inpatient* patient = _getInpatient(healthCardNumber, containedIn);

    if (!patient)
    {
        return false;
    }

    containedIn->remove(healthCardNumber);
    delete patient;

    return true;
}

/**
 * Gets the Inpatient pointer with the given health card num.
 *
 * @param QString health card number of patient being request
 * @return Inpatient* with given healthCardNum or NULL if it's not in the facility
 */
Inpatient* Facility::getInpatient(QString& healthCardNum)
{
    PatientContainer* temp;
    return _getInpatient(healthCardNum, temp);
}

/**
 * Gets the Inpatient pointer with the given health card num, as well as which bed their in.
 *
 * @param QString health card number of patient being request
 * @param PatientContainer the container the patient is in (aka which bed their in)
 * @return Inpatient* with given healthCardNum or NULL if it's not in the facility
 */
Inpatient* Facility::_getInpatient(QString& healthCardNum, PatientContainer*& outContainedIn)
{
    Inpatient* patient = 0;

    // Goes through each container of patients to find them.
    // O(1) since its O(1) per find * n (n = num of bed types)
    foreach(PatientContainer* container, _patients)
    {
        PatientContainer::iterator iter = container->find(healthCardNum);
        if (iter != container->end())
        {
            patient = *iter;
            outContainedIn = container;
        }
    }

    return patient;
}

void Facility::addBeds(unsigned num, CareType type)
{
    PatientContainer* patients;
    int *numBeds;
    _getPointersForType(type, patients, numBeds);

    *numBeds += num;
}

void Facility::decreaseBeds(unsigned num, CareType type)
{
    PatientContainer* patients;
    int *numBeds;
    _getPointersForType(type, patients, numBeds);

    if (*numBeds - (int)num < patients->size())
    {
        /// @todo Figure out what to do here...
    }
    else if ((*numBeds - (int)num) < 0)
    {
        /// @todo Decide if this is right
        *numBeds = 0;
    }
    else
    {
        *numBeds -= num;
    }
}

int Facility::getNumBeds(CareType type)
{
    PatientContainer* temp;
    int* numBeds;
    _getPointersForType(type, temp, numBeds);

    return *numBeds;
}

inline void Facility::_getPointersForType(CareType type, PatientContainer* &container, int* &numBeds)
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
        break;
    }
}
