#include "patient.h"

Patient::Patient(QString &healthCardNumber, QString& name, QDate &placedOnWaitingList)
    : _healthCardNumber(healthCardNumber), _name(name), _placedOnWL(placedOnWaitingList)
{
}

Patient::~Patient()
{
}

QString& Patient::getHealthCardNumber()
{
    return _healthCardNumber;
}