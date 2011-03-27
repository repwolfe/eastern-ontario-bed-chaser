#include "changedatacontrol.h"

ChangeDataControl::ChangeDataControl()
{
    _movePatientControl = new MovePatientControl();
}

ChangeDataControl::~ChangeDataControl()
{
    delete _movePatientControl;
}

/// @todo remove this
void ChangeDataControl::run()
{
    displayMovePatientsToBedForm();
  //  displayMovePatientsToFacilityForm();
}

/// @todo implement this
bool ChangeDataControl::changeData(QString &args, QString &data)
{
    return true;
}

/****************************************
 *                SLOTS                 *
 ****************************************/

void ChangeDataControl::displayMovePatientsToBedForm()
{
    _movePatientControl->showToBedForm();
}

void ChangeDataControl::displayMovePatientsToFacilityForm()
{
    _movePatientControl->showToFacilityForm();
}
