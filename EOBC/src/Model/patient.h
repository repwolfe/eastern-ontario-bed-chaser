#ifndef PATIENT_H
#define PATIENT_H

#include <QDate>
#include "modelcommon.h"

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
    Patient(QString& hcn, QString& first, QString& last, CareType requiredCare);
    Patient(QString& hcn, QString& first, QString& last, CareType requiredCare, QDate& placedOnWL);
    Patient(QString& hcn, QString& first, QString& last, CareType requiredCare, CareType occuringCare, QDate& placedOnWL, QDate& admitted);
    ~Patient();

    const QString& getHealthCardNumber() const;
    const QString& getFirstName() const;
    const QString& getLastName() const;
    const QString getName() const;

    CareType getRequiredCare() const;
    CareType getOccuringCare() const;

    const QDate& getDatePlacedOnWaitingList() const;
    const QDate& getAdmissionDate() const;

    void setRequiredCare(CareType care);
    void setOccuringCare(CareType care);

    void setDatePlacedonWaitingList(QDate& date);
    void setAdmissionDate(QDate& date);

private:
    QString _healthCardNumber;
    QString _firstName;
    QString _lastName;

    CareType _requiredCare;
    CareType _occuringCare; /// @todo occCare == occuringCare?

    QDate _placedOnWL;
    QDate _admitted;
};

#endif // PATIENT_H
