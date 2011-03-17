#ifndef INPATIENT_H
#define INPATIENT_H

#include "patient.h"

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
