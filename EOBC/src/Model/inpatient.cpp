#include "inpatient.h"

Inpatient::Inpatient(QString& healthCardNumber, QDate& placedOnWaitingList, QDate& admissionDate)
    : Patient(healthCardNumber, placedOnWaitingList), _admissionDate(admissionDate)
{
}

Inpatient::Inpatient(Patient& patient, QDate& admissionDate)
    : Patient(patient), _admissionDate(admissionDate)
{

}


/**
 * Takes in a patient, returns an inpatient from it and deletes the original.
 * Makes the original pointer NULL
 *
 * @param Patient* the Patient to convert to an inpatient
 * @return Inpatient*
 */
Inpatient* Inpatient::convertToInpatient(Patient*& patient, QDate& admissionDate)
{
    Inpatient* inpatient = new Inpatient(*patient, admissionDate);
    patient = 0;
    return inpatient;
}
