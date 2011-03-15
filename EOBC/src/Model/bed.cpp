#include "bed.h"

/**
 * One argument contructor, sets the owned patient to NULL
 *
 * @param CareType the type of care
 */
Bed::Bed(CareType caretype)
{
    Bed(caretype, 0);
}

/**
 * Constructor, takes ownership of patient
 *
 * @param CareType the type of case
 * @param InPatient the patient in this bed
 */
Bed::Bed(CareType caretype, Inpatient *patient)
    : _careType(caretype), _patient(patient)
{
}

Bed::~Bed()
{
    delete _patient;
}

/**
 * Set the patient in this bed to something else.
 * Deletes the old patient.
 *
 * @param Inpatient the new patient to store
 */
void Bed::setPatient(Inpatient *patient)
{
    if (_patient != patient)
    {
        delete _patient;
        _patient = patient;
    }
}

