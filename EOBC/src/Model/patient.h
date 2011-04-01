#ifndef PATIENT_H
#define PATIENT_H

#include <QDate>
#include <QMap>
#include "modelcommon.h"
#include "logger.h"

using EOBC::CareType;

/**
 * @brief Object representation of a Patient.
 *
 * Patients have a health card number and a name.
 * They are people requiring care and are trying to
 * be placed in a particular Facility or Area.
 *
 * This class is part of the Model subsystem described in D2.
 */
class Patient
{
public:
    Patient(QString hcn, QString first, QString last, CareType requiredCare);
    Patient(QString hcn, QString first, QString last, CareType requiredCare, QDate placedOnWL);
    Patient(QString hcn, QString first, QString last, CareType requiredCare, CareType occupiedCare, QDate admitted);
    Patient(QString hcn, QString first, QString last, CareType requiredCare, CareType occupiedCare, QDate placedOnWL, QDate admitted);
    ~Patient();

    const QString& getHealthCardNumber() const;
    const QString& getFirstName() const;
    const QString& getLastName() const;
    const QString getName() const;

    CareType getRequiredCare() const;
    CareType getOccupiedCare() const;

    const QDate& getDatePlacedOnWaitingList() const;
    const QDate& getAdmissionDate() const;

    void setRequiredCare(CareType care);
    void setOccupiedCare(CareType care);

    void setDatePlacedOnWaitingList(QDate date);
    void setAdmissionDate(QDate date);

    void makeInpatient(QDate admissionDate, CareType occupiedCare);	/// @todo make sure this function is right
    bool isInpatient() const;

    const QString toString() const;

private:
    QString _healthCardNumber;
    QString _firstName;
    QString _lastName;

    CareType _requiredCare;
    CareType _occupiedCare;

    QDate _placedOnWL;
    QDate _admitted;

    bool _inpatient;
};

/// A list of Patients
typedef QMap<QString, Patient*> WaitingList;

#endif // PATIENT_H
