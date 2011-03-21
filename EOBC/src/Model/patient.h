#ifndef PATIENT_H
#define PATIENT_H

#include <QDate>

/**
 * Patients have a health card number and a name.
 * They are people requiring care and are trying to
 * be placed in a particular Facility or Area.
 *
 * This class is part of the Model subsystem described in D2.
 */
class Patient
{
public:
    Patient(QString& healthCardNumber, QString& name, QDate& placedOnWaitingList);
    virtual ~Patient();

    QString& getHealthCardNumber();

private:
    QString _healthCardNumber;
    QString _name;
    QDate _placedOnWL;
};

#endif // PATIENT_H
