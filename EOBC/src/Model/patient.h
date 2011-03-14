#ifndef PATIENT_H
#define PATIENT_H

#include <QDate>

class Patient
{
public:
    Patient(QString& healthCardNumber, QDate& placedOnWaitingList);

private:
    QString _healthCardNumber;
    QDate _placedOnWL;
};

#endif // PATIENT_H
