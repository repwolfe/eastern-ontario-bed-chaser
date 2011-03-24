#include "movepatientform.h"

MovePatientForm::MovePatientForm(bool displayBedType, QString moveTo, QWidget *parent) :
    QWidget(parent), _displayBedType(displayBedType), _moveToLabel(moveTo)
{
}
