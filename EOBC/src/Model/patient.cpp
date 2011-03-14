#include "patient.h"

Patient::Patient(QString &healthCardNumber, QDate &placedOnWaitingList)
    : _healthCardNumber(healthCardNumber), _placedOnWL(placedOnWaitingList)
{
}
