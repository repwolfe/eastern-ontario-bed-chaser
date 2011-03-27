#include "movepatientcontrol.h"

MovePatientControl::MovePatientControl()
{
    _toFacilityForm = new MovePatientForm("Move Patients to Facility", false, "To Facility");
    _toBedForm = new MovePatientForm("Move Patients to Bed", true, "To Bed");

    QStringList bedOptions;
    bedOptions.push_back("AC");
    bedOptions.push_back("CCC");
    /// @todo what to do about this
    bedOptions.push_back("LTC");
    _toBedForm->setMoveToItems(bedOptions);

    /// @todo remove this, get real patients somehow:
    QStringList patients;
    patients.push_back("Robbie");
    patients.push_back("JP");
    patients.push_back("Austin");

    QStringList facilities;
    facilities.push_back("Franklin General");
    facilities.push_back("Cedar Sinar");
    _toBedForm->setFacilityItems(facilities);
    _toBedForm->setPatientItems(patients);

    _setupConnections();
}

MovePatientControl::~MovePatientControl()
{
    delete _toFacilityForm;
    delete _toBedForm;
}

void MovePatientControl::showToFacilityForm()
{
    _toFacilityForm->show();
}

void MovePatientControl::showToBedForm()
{
    _toBedForm->show();
}

void MovePatientControl::_setupConnections()
{
    connect(_toBedForm->getMoveToList(), SIGNAL(currentIndexChanged(QString)), SLOT(toBedFormPatientMoved(QString)));
    connect(_toFacilityForm->getMoveToList(), SIGNAL(currentIndexChanged(QString)), SLOT(toFacilityFormPatientMoved(QString)));
    connect(_toBedForm->getPatientList(), SIGNAL(itemSelectionChanged()), SLOT(toBedFormPatientSelected()));
}

/**
 * Private function to store changes when patients are moved
 *
 * @param moveTo where they were moved
 * @param moveToMap which map to store this change
 */
void MovePatientControl::_patientMoved(QString moveTo, QMap<QString, QString>* moveToMap, MovePatientForm* form)
{
    const QListWidget* patientList = form->getPatientList();
    // Find out who was moved
    if (patientList->currentRow() != -1)
    {
        const QString& patientHCN = patientList->currentItem()->text();
        (*moveToMap)[patientHCN] = moveTo;
    }
}

/****************************************
 *               SIGNALS                *
 ****************************************/

/**
 * Everytime a patient with a specific health card number is moved
 * anywhere, the change stored in the map
 *
 * @param moveTo where they were moved
 */
void MovePatientControl::toFacilityFormPatientMoved(QString moveTo)
{
    _patientMoved(moveTo, &_facilityMoveToChanges, _toFacilityForm);
}

/**
 * Everytime a patient with a specific health card number is moved
 * anywhere, the change stored in the map
 *
 * @param moveTo where they were moved
 */
void MovePatientControl::toBedFormPatientMoved(QString moveTo)
{
    /// @todo try and avoid redundant changes (bed == AC, bed --> CCC, bed --> AC)
    _patientMoved(moveTo, &_bedMoveToChanges, _toBedForm);
}

/**
 * @todo find better use for this
 */
void MovePatientControl::toBedFormPatientSelected()
{

}
