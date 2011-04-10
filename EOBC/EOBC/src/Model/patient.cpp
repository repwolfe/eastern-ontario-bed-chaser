#include "patient.h"

/**
 * Constructor for Patient, not on a Waiting List or in a Facility
 * Constructs 1/1/1 date for date admitted and date placed on waiting list
 *
 * @param hcn the Health Card Number of the Patient
 * @param first the Patient's first name
 * @param last the Patient's last name
 * @param requiredCare the type of care required by the patient
 */
Patient::Patient(QString hcn, QString first, QString last, CareType requiredCare)
    : _healthCardNumber(hcn), _firstName(first), _lastName(last), _requiredCare(requiredCare)
    , _placedOnWL(QDate(1,1,1)), _admitted(QDate(1,1,1)),  _inpatient(false)
{

}

/**
 * Constructor for Patient, on a Waiting List but not in a Facility
 * Constructs 1/1/1 date for date admitted
 *
 * @param hcn the Health Card Number of the Patient
 * @param first the Patient's first name
 * @param last the Patient's last name
 * @param requiredCare the type of care required by the patient
 * @param placedOnWL date placed on a waiting list
 */
Patient::Patient(QString hcn, QString first, QString last, CareType requiredCare, QDate placedOnWL)
    : _healthCardNumber(hcn), _firstName(first), _lastName(last), _requiredCare(requiredCare), _placedOnWL(placedOnWL), _admitted(QDate(1,1,1)), _inpatient(false)
{

}

/**
 * Constructor for Patient, not on a Waiting List but in a Facility
 * Contructs 1/1/1 date for date placed on waiting list
 *
 * @param hcn the Health Card Number of the Patient
 * @param first the Patient's first name
 * @param last the Patient's last name
 * @param requiredCare the type of care required by the patient
 * @param occupiedCare the type of care the patient is actually getting
 * @param admitted date admitted in a Facility
 */
Patient::Patient(QString hcn, QString first, QString last, CareType requiredCare, CareType occupiedCare, QDate admitted)
    : _healthCardNumber(hcn), _firstName(first), _lastName(last), _requiredCare(requiredCare), _occupiedCare(occupiedCare)
    , _placedOnWL(QDate(1,1,1)), _admitted(admitted), _inpatient(true)
{

}

/**
 * Constructor for Patient, on a Waiting List and in a Facility
 *
 * @param hcn the Health Card Number of the Patient
 * @param first the Patient's first name
 * @param last the Patient's last name
 * @param requiredCare the type of care required by the patient
 * @param occupiedCare the type of care the patient is actually getting
 * @param placedOnWL date placed on a waiting list
 * @param admitted date admitted in a Facility
 */
Patient::Patient(QString hcn, QString first, QString last, CareType requiredCare, CareType occupiedCare, QDate placedOnWL, QDate admitted)
    : _healthCardNumber(hcn), _firstName(first), _lastName(last), _requiredCare(requiredCare), _occupiedCare(occupiedCare)
    , _placedOnWL(placedOnWL), _admitted(admitted), _inpatient(true)
{

}

Patient::~Patient()
{
}

const QString& Patient::getHealthCardNumber() const
{
    return _healthCardNumber;
}

const QString& Patient::getFirstName() const
{
    return _firstName;
}

const QString& Patient::getLastName() const
{
    return _lastName;
}

const QString Patient::getName() const
{
    return _firstName + " " + _lastName;
}

CareType Patient::getRequiredCare() const
{
    return _requiredCare;
}

CareType Patient::getOccupiedCare() const
{
    return _occupiedCare;
}

const QDate& Patient::getDatePlacedOnWaitingList() const
{
    return _placedOnWL;
}

const QDate& Patient::getAdmissionDate() const
{
    return _admitted;
}

void Patient::setRequiredCare(CareType care)
{
    _requiredCare = care;
}

void Patient::setOccupiedCare(CareType care)
{
    _occupiedCare = care;
}

void Patient::setDatePlacedOnWaitingList(QDate date)
{
    _placedOnWL = date;
}

void Patient::setAdmissionDate(QDate date)
{
    _admitted = date;
}

/**
 * Makes a Patient into an Inpatient
 *
 * @param admissionDate the date they were admitted to a Facility
 * @param occupiedCare the type of care they are getting
 */
void Patient::makeInpatient(QDate admissionDate, CareType occupiedCare)
{
    if (!_inpatient)
    {
	Logger::errorMessage("Patient", "makeInpatient()", "Called on an Inpatient");
	return;
    }
    _inpatient = true;
    setAdmissionDate(admissionDate);
    setOccupiedCare(occupiedCare);
}

/**
 * Returns if the Patient is an Inpatient
 *
 * @return The value of Inpatient
 */
bool Patient::isInpatient() const
{
    return _inpatient;
}

const QString Patient::toString() const
{
    return getName() + ": " + getHealthCardNumber();
}
