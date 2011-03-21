#include "inpatient.h"

Inpatient::Inpatient(QString& healthCardNumber, QString& name, QDate& placedOnWaitingList, QDate& admissionDate)
    : Patient(healthCardNumber, name, placedOnWaitingList)
    , _admissionDate(admissionDate)
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
    // If it's already an inpatient
    Inpatient* inpatient = dynamic_cast<Inpatient*>(patient);
    if (inpatient)
    {
        return inpatient;
    }

    inpatient = new Inpatient(*patient, admissionDate);
    delete patient;
    patient = 0;
    return inpatient;
}
