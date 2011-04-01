#include "movepatientcontrol.h"
#include "convenience.h"

MovePatientControl::MovePatientControl()
{
    // Create the two forms
    _toFacilityForm = new MovePatientForm("Move Patients to Facility", false, "To Facility", true);
    _toBedForm = new MovePatientForm("Move Patients to Bed", true, "To Bed", false);

    _addPatientControl = new AddPatientControl();

    // Set the options for moving a patient to a bed
    QStringList bedOptions;
    bedOptions.push_back("AC");
    bedOptions.push_back("CCC");
    /// @todo what to do about this
    bedOptions.push_back("LTC");
    _toBedForm->setMoveToItems(bedOptions);

    /// @todo remove this, get real patients somehow:
    QMap<QString, QString> patients;
    patients["Robbie Wolfe"] = "1233-123-123";
    patients["JP Landry"] = "5535-234-123";
    patients["Chuck Norris"] = "1233-323-154";
    patients["Austin Chamney"] = "3213-999-123";

    QMap<QString,QString> patientsToBed;
    patientsToBed["1233-123-123"] = "CCC";
    patientsToBed["5553-234-123"] = "LTC";
    patientsToBed["3213-999-123"] = "AC";
    patientsToBed["1233-323-154"] = "AC";
    setPatientToBedMap(patientsToBed);

    QStringList facilities;
    facilities.push_back("Franklin General");
    facilities.push_back("Cedar Sinar");
    _toBedForm->setFacilityItems(facilities);
    _toBedForm->setPatientItems(patients, patientsToBed);

    _setupConnections();
}

MovePatientControl::~MovePatientControl()
{
    delete _toFacilityForm;
    delete _toBedForm;
    delete _addPatientControl;
}

void MovePatientControl::setFacilitiesList(const QMap<ID, QString>& data)
{
    /// @todo implement
}

void MovePatientControl::setFacilitiesToPatients(const QMap<ID, QLinkedList<Patient*> >& data)
{
    /// @todo implement
}

void MovePatientControl::setPatientToBedMap(QMap<QString,QString>& inMap)
{
    /// @todo implement
}

const QMap<QString, QString>& MovePatientControl::getBedChanges() const
{
    return _bedMoveToChanges;
}
const QMap<QString, QString>& MovePatientControl::getFacilityChanges() const
{
    return _facilityMoveToChanges;
}

void MovePatientControl::showToFacilityForm()
{
    _facilityMoveToChanges.clear();
    _toFacilityForm->show();
}

void MovePatientControl::showToBedForm()
{
    _bedMoveToChanges.clear();
    _toBedForm->show();
}

void MovePatientControl::_setupConnections()
{
    connect(_toBedForm, SIGNAL(patientMoved(QString)), SLOT(_toBedFormPatientMoved(QString)));
    connect(_toFacilityForm, SIGNAL(patientMoved(QString)), SLOT(_toFacilityFormPatientMoved(QString)));

    connect(_toBedForm, SIGNAL(patientSelected(QString)), SLOT(_toBedFormPatientSelected(QString)));

    connect(_toBedForm, SIGNAL(submitButtonClicked()), SLOT(_toBedFormSubmit()));
    connect(_toBedForm, SIGNAL(cancelButtonClicked()), SLOT(_toBedFormCancel()));

    connect(_toFacilityForm, SIGNAL(addPatientClicked()), SLOT(_toFacilityFormAddPatient()));
    connect(_toFacilityForm, SIGNAL(removePatientClicked()), SLOT(_toFacilityFormRemovePatient()));
    connect(_addPatientControl, SIGNAL(submitClicked(QString,QString,QString,QString)), SLOT(_patientCreated(QString,QString,QString,QString)));

    connect(_toFacilityForm, SIGNAL(submitButtonClicked()), SLOT(_toFacilityFormSubmit()));
    connect(_toFacilityForm, SIGNAL(cancelButtonClicked()), SLOT(_toFacilityFormCancel()));
}

const QLinkedList<QString>& MovePatientControl::getPatientsRemoved() const
{
    return _patientsRemoved;
}

const QLinkedList<Patient>& MovePatientControl::getPatientsAdded() const
{
    return _patientsAdded;
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
void MovePatientControl::_toFacilityFormPatientMoved(QString moveTo)
{
    QString patientHCN;
    if (_toFacilityForm->getCurrentPatient(patientHCN))
    {
        _facilityMoveToChanges[patientHCN] = moveTo;
    }
}

/**
 * Everytime a patient with a specific health card number is moved
 * anywhere, the change stored in the map
 *
 * @param moveTo where they were moved
 */
void MovePatientControl::_toBedFormPatientMoved(QString moveTo)
{
    QString patientHCN;
    if (_toBedForm->getCurrentPatient(patientHCN))
    {
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
 * When a patient is selected, set the "Move To" option to be their
 * current bed
 *
 * @param item The Patient selected
 */
void MovePatientControl::_toBedFormPatientSelected(QString item)
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

void MovePatientControl::_toBedFormSubmit()
{
    _toBedForm->close();
    emit toBedFormSubmitClicked();
}

void MovePatientControl::_toBedFormCancel()
{
    _toBedForm->close();
    _bedMoveToChanges.clear();
}

void MovePatientControl::_toFacilityFormAddPatient()
{
    _addPatientControl->showForm();
}

void MovePatientControl::_toFacilityFormRemovePatient()
{
    QString patientHCN;
    if (_toFacilityForm->getCurrentPatient(patientHCN))
    {
        _patientsRemoved.push_back(patientHCN);
        _toFacilityForm->removeSelectedPatientItem();
    }
}

void MovePatientControl::_toFacilityFormSubmit()
{
    _toFacilityForm->close();
    emit toFacilityFormSubmitClicked();
}

void MovePatientControl::_toFacilityFormCancel()
{
    _toFacilityForm->close();
    _facilityMoveToChanges.clear();
}

void MovePatientControl::_patientCreated(QString firstName, QString lastName, QString hcn, QString requiredCare)
{
    // Don't add a patient already in the Facility
    if (!_toFacilityForm->isPatientInList(hcn))
    {
        Patient patient(hcn, firstName, lastName, Convenience::qstringToCareType(requiredCare));
        patient.setDatePlacedOnWaitingList(QDate::currentDate());
        _patientsAdded.push_back(patient);
        _toFacilityForm->addPatientItem(patient.getName(), hcn);
    }
}

