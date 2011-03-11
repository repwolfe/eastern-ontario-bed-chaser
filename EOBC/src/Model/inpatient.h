#ifndef INPATIENT_H
#define INPATIENT_H

#include "patient.h"
#include <QDate>

class Inpatient : public Patient
{
public:
    Inpatient(QDate& admissionDate);

private:
    QDate _admissionDate;
};

#endif // INPATIENT_H
