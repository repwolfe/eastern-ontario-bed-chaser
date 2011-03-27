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

    QMap<QString,QString> patientsToBed;
    patientsToBed["Robbie"] = "CCC";
    patientsToBed["JP"] = "LTC";
    patientsToBed["Austin"] = "AC";
    setPatientToBedMap(patientsToBed);

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

void MovePatientControl::setPatientToBedMap(QMap<QString,QString>& inMap)
{
    _patientToBed = inMap;
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
    connect(_toBedForm, SIGNAL(patientMoved(QString)), SLOT(toBedFormPatientMoved(QString)));
    connect(_toFacilityForm, SIGNAL(patientMoved(QString)), SLOT(toFacilityFormPatientMoved(QString)));

    connect(_toBedForm, SIGNAL(patientSelected(QString)), SLOT(toBedFormPatientSelected(QString)));

    connect(_toBedForm, SIGNAL(submitButtonClicked()), SLOT(toBedFormSubmit()));
    connect(_toBedForm, SIGNAL(cancelButtonClicked()), SLOT(toBedFormCancel()));
    connect(_toFacilityForm, SIGNAL(submitButtonClicked()), SLOT(toFacilityFormSubmit()));
    connect(_toFacilityForm, SIGNAL(cancelButtonClicked()), SLOT(toFacilityFormCancel()));
}

/****************************************
 *                SLOTS                 *
 ****************************************/

/**
 * Everytime a patient with a specific health card number is moved
 * anywhere, the change stored in the map
 *
 * @param moveTo where they were moved
 */
void MovePatientControl::toFacilityFormPatientMoved(QString moveTo)
{
    // Find out who was moved
    if (_toFacilityForm->getCurrentPatientRow() != -1)
    {
        const QString& patientHCN = _toFacilityForm->getCurrentPatient();
        _facilityMoveToChanges[patientHCN] = moveTo;
    }
}

/**
 * Everytime a patient with a specific health card number is moved
 * anywhere, the change stored in the map
 *
 * @param moveTo where they were moved
 */
void MovePatientControl::toBedFormPatientMoved(QString moveTo)
{
    // Find out who was moved
    if (_toBedForm->getCurrentPatientRow() != -1)
    {
        const QString& patientHCN = _toBedForm->getCurrentPatient();
        // Avoid redundant changes (bed == AC, bed --> CCC, bed --> AC)
        if (_patientToBed[patientHCN] != moveTo)
        {
            _bedMoveToChanges[patientHCN] = moveTo;
        }
        else
        {
            // Moved from original bed to something else back to original
            // remove the change since it will be redundant
            _bedMoveToChanges.remove(patientHCN);
        }
    }
}

/**
 * @todo find better use for this
 */
void MovePatientControl::toBedFormPatientSelected(QString item)
{
    QMap<QString, QString>::const_iterator iter = _patientToBed.find(item);

    if (iter != _patientToBed.end())
    {
        int index = 0;
        const QString& bed = iter.value();
        if (bed == "AC") { index = 0; }
        else if (bed == "CCC") { index = 1; }
        else if (bed == "LTC") { index = 2; }

        _toBedForm->setCurrentMoveToItem(index);
    }
}

void MovePatientControl::toBedFormSubmit()
{
    _toBedForm->close();
}

void MovePatientControl::toBedFormCancel()
{
    _toBedForm->close();
    _bedMoveToChanges.clear();
}

void MovePatientControl::toFacilityFormSubmit()
{
    _toFacilityForm->close();
}

void MovePatientControl::toFacilityFormCancel()
{
    _toFacilityForm->close();
    _facilityMoveToChanges.clear();
}
