#include "patient.h"

Patient::Patient(QString& hcn, QString& first, QString& last, CareType requiredCare)
    : _healthCardNumber(hcn), _firstName(first), _lastName(last), _requiredCare(requiredCare)
{

}

Patient::Patient(QString& hcn, QString& first, QString& last, CareType requiredCare, QDate& placedOnWL)
    : _healthCardNumber(hcn), _firstName(first), _lastName(last), _requiredCare(requiredCare), _placedOnWL(placedOnWL)
{

}

Patient::Patient(QString& hcn, QString& first, QString& last, CareType requiredCare, CareType occuringCare, QDate& placedOnWL, QDate& admitted)
    : _healthCardNumber(hcn), _firstName(first), _lastName(last), _requiredCare(requiredCare), _occuringCare(occuringCare)
    , _placedOnWL(placedOnWL), _admitted(admitted)
{

}

Patient::~Patient()
{

}

const QString& Patient::getHealthCardNumber() const
{
    return _healthCardNumber;
}

const QString& Patient::getFirstName() const
{
    return _firstName;
}

const QString& Patient::getLastName() const
{
    return _lastName;
}

const QString Patient::getName() const
{
    return _firstName + " " + _lastName;
}

CareType Patient::getRequiredCare() const
{
    return _requiredCare;
}

CareType Patient::getOccuringCare() const
{
    return _occuringCare;
}

const QDate& Patient::getDatePlacedOnWaitingList() const
{
    return _placedOnWL;
}

const QDate& Patient::getAdmissionDate() const
{
    return _admitted;
}

void Patient::setRequiredCare(CareType care)
{
    _requiredCare = care;
}

void Patient::setOccuringCare(CareType care)
{
    _occuringCare = care;
}

void Patient::setDatePlacedonWaitingList(QDate& date)
{
    _placedOnWL = date;
}

void Patient::setAdmissionDate(QDate& date)
{
    _admitted = date;
}
