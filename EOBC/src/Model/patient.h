#ifndef PATIENT_H
#define PATIENT_H

#include <QDate>

class Patient
{
public:
    Patient(QString& healthCardNumber, QString& name, QDate& placedOnWaitingList);

private:
    QString _healthCardNumber;
    QString _name;
    QDate _placedOnWL;
};

#endif // PATIENT_H
