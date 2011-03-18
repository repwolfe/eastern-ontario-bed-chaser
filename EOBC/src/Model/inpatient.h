#ifndef INPATIENT_H
#define INPATIENT_H

#include "patient.h"

/**
 * Inpatient's are Patient's that have been placed in a facility.
 *
 * @todo consider just making Patient's have a state instead of this class.
 *
 * This class is part of the Model subsystem described in D2.
 */
class Inpatient : public Patient
{
public:
    Inpatient(QString& healthCardNumber, QString& name, QDate& placedOnWaitingList, QDate& admissionDate);
    Inpatient(Patient& patient, QDate& admissionDate);


    static Inpatient* convertToInpatient(Patient*& patient, QDate& admissionDate);

private:
    QDate _admissionDate;
};

#endif // INPATIENT_H
