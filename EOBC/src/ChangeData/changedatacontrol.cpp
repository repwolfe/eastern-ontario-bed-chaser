#include "changedatacontrol.h"

ChangeDataControl::ChangeDataControl()
{
    _movePatientControl = new MovePatientControl();
    _addFacilityControl = new AddFacilityControl();
    _addPatientControl  = new AddPatientControl();

    connect(_movePatientControl, SIGNAL(toBedFormSubmitClicked()), SLOT(movePatientsToBedSubmitted()));
    connect(_movePatientControl, SIGNAL(toFacilityFormSubmitClicked()), SLOT(movePatientsToFacilitySubmitted()));
    connect(_addFacilityControl, SIGNAL(submitClicked(QString,QString,QString)),
            SLOT(addFacilitySubmitted(QString,QString,QString)));
    connect(_addPatientControl, SIGNAL(submitClicked(QString,QString,QString,QString)),
            SLOT(addPatientSubmitted(QString,QString,QString,QString)));
}

ChangeDataControl::~ChangeDataControl()
{
    delete _movePatientControl;
    delete _addFacilityControl;
    delete _addPatientControl;
}

/// @todo remove this
void ChangeDataControl::run()
{
  //  displayMovePatientsToBedForm();
  //  displayMovePatientsToFacilityForm();
  //  displayAddFacilityForm();
  //  displayAddPatientForm();
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

void ChangeDataControl::displayAddFacilityForm()
{
    _addFacilityControl->showForm();
}

void ChangeDataControl::displayAddPatientForm()
{
    _addPatientControl->showForm();
}

void ChangeDataControl::movePatientsToBedSubmitted()
{
    const QMap<QString, QString>& changes = _movePatientControl->getBedChanges();
    /// @todo send changes to StorageWrite
    changes.count();
}

void ChangeDataControl::movePatientsToFacilitySubmitted()
{
    const QMap<QString, QString>& changes = _movePatientControl->getFacilityChanges();
    /// @todo send changes to StorageWrite
    changes.count();
}

void ChangeDataControl::addFacilitySubmitted(QString, QString, QString)
{
    /// @todo send the facilityname, x-axis and y-axis to StorageWrite
}

void ChangeDataControl::addPatientSubmitted(QString, QString, QString, QString)
{
    /// @todo send the firstname, lastname, healthcardnum and required care to StorageWrite
}
