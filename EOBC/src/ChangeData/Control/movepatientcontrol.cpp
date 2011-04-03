#include "movepatientcontrol.h"
#include "convenience.h"
#include "logger.h"

MovePatientControl::MovePatientControl()
{
    // Create the two forms
    _toFacilityForm = new MovePatientForm("Move Patients to Facility", false, "To Facility", false);
    _toBedForm = new MovePatientForm("Move Patients to Bed", true, "To Bed", true);

    _addPatientControl = new AddPatientControl(true);

    _tfWaitingForFacilitiesList = false;
    _tfcurrentFacilityIndex = 0;

    _tbWaitingForFacilitiesList = false;
    _tbcurrentFacilityIndex = 0;

    // Set the options for moving a patient to a bed
    QStringList bedOptions;
    bedOptions.push_back("AC");
    bedOptions.push_back("CCC");
    /// @todo what to do about this
    bedOptions.push_back("LTC");
    _toBedForm->setMoveToItems(bedOptions);

    _setupConnections();
}

MovePatientControl::~MovePatientControl()
{
    delete _toFacilityForm;
    delete _toBedForm;
    delete _addPatientControl;
}

/**
 * Upon receiving the list of facilities, give it to whichever form needs it
 *
 * @param data a map of facility Id to their Name
 */
void MovePatientControl::setFacilitiesList(const QMap<ID, QString>& data)
{
    QStringList facilities;
    QMap<int, ID> indexToFacilityId;
    if (_tfWaitingForFacilitiesList || _tbWaitingForFacilitiesList)
    {
        QMap<ID, QString>::const_iterator iter = data.begin();
        int index = 0;
        while (iter != data.end())
        {
            facilities << iter.value();
            indexToFacilityId[index] = iter.key();
            ++index;
            ++iter;
        }
    }

    if (_tfWaitingForFacilitiesList)
    {
        _tfWaitingForFacilitiesList = false;
        _toFacilityForm->setFacilityItems(facilities);
	_toFacilityForm->setMoveToItems(facilities);
        _tfIndexToID = indexToFacilityId;
    }

    /// @todo decide if this should be a else if
    if (_tbWaitingForFacilitiesList)
    {
        _tbWaitingForFacilitiesList = false;
        _toBedForm->setFacilityItems(facilities);
        _tbIndexToID = indexToFacilityId;
    }
}

/**
 * Upon receiving the map of facilities to their patients, give it to whichever form needs it
 *
 * @param data map of facilities to their patients
 */
void MovePatientControl::setFacilitiesToPatients(const QMap<ID, QLinkedList<Patient*> >& data)
{
    FacilityIDToPatientInfo facilitiesToPatientInfo;
    // If either form needs it, generate new map
    if (_tfWaitingForFacilitiesPatients || _tbWaitingForFacilitiesPatients)
    {
        QMap<ID, QLinkedList<Patient*> >::const_iterator iter = data.begin();
        while (iter != data.end())
        {
            QMap<QString, QPair<QString, QString> > patientIdToNameAndBed;
            foreach (Patient* patient, iter.value())
            {
                patientIdToNameAndBed[patient->getHealthCardNumber()] = qMakePair(patient->getName(),
                                                                                  Convenience::careTypeToQString(patient->getOccupiedCare()));
            }
            facilitiesToPatientInfo[iter.key()] = patientIdToNameAndBed;
            ++iter;
        }
    }

    if (_tfWaitingForFacilitiesPatients)
    {
        _tfWaitingForFacilitiesPatients = false;
        _tfFacilityToPatientsInfo = facilitiesToPatientInfo;

        // If we have the patient info now and finished waiting for facilities, populate form
        if (!_tfWaitingForFacilitiesList)
        {
            _toFacilityFormFacilitySelected(_tfcurrentFacilityIndex);
        }
    }

    /// @todo decide if this should be a else if
    if (_tbWaitingForFacilitiesPatients)
    {
        _tbWaitingForFacilitiesPatients = false;
        _tbFacilityToPatientsInfo = facilitiesToPatientInfo;

        // If we have the patient info now and finished waiting for facilities, populate form
        if (!_tbWaitingForFacilitiesList)
        {
            _toBedFormFacilitySelected(_tbcurrentFacilityIndex);
        }
    }
}

const QMap<QString, QString>& MovePatientControl::getBedChanges() const
{
    return _bedMoveToChanges;
}
const QMap<QString, ID>& MovePatientControl::getFacilityChanges() const
{
    return _facilityMoveToChanges;
}

void MovePatientControl::toFacilityFormWaitingForInfo()
{
    _tfWaitingForFacilitiesList = true;
    _tfWaitingForFacilitiesPatients = true;
}

void MovePatientControl::showToFacilityForm()
{
    _facilityMoveToChanges.clear();
    _patientsAdded.clear();
    _patientsRemoved.clear();
    _toFacilityForm->show();
    /// @todo clear form gui?

}

void MovePatientControl::toBedFormWaitingForInfo()
{
    _tbWaitingForFacilitiesList = true;
    _tbWaitingForFacilitiesPatients = true;
}

void MovePatientControl::showToBedForm()
{
    _bedMoveToChanges.clear();
    _toBedForm->show();
    /// @todo clear form gui?
}

void MovePatientControl::_setupConnections()
{
    connect(_toBedForm, SIGNAL(patientMoved(QString)), SLOT(_toBedFormPatientMoved(QString)));
    connect(_toFacilityForm, SIGNAL(patientMoved(int)), SLOT(_toFacilityFormPatientMoved(int)));

    connect(_toBedForm, SIGNAL(patientSelected(QString)), SLOT(_toBedFormPatientSelected(QString)));
    connect(_toFacilityForm, SIGNAL(patientSelected(QString)), SLOT(_toFacilityFormPatientSelected()));

    connect(_toBedForm, SIGNAL(submitButtonClicked()), SLOT(_toBedFormSubmit()));
    connect(_toBedForm, SIGNAL(cancelButtonClicked()), SLOT(_toBedFormCancel()));

    connect(_toBedForm, SIGNAL(addPatientClicked()), SLOT(_toBedFormAddPatient()));
    connect(_toBedForm, SIGNAL(removePatientClicked()), SLOT(_toBedFormRemovePatient()));
    connect(_addPatientControl, SIGNAL(submitClicked(QString,QString,QString,QString,QDate,QString)), SLOT(_patientCreated(QString,QString,QString,QString,QDate,QString)));

    connect(_toFacilityForm, SIGNAL(submitButtonClicked()), SLOT(_toFacilityFormSubmit()));
    connect(_toFacilityForm, SIGNAL(cancelButtonClicked()), SLOT(_toFacilityFormCancel()));

    connect(_toFacilityForm, SIGNAL(facilitySelected(int)), SLOT(_toFacilityFormFacilitySelected(int)));
    connect(_toBedForm, SIGNAL(facilitySelected(int)), SLOT(_toBedFormFacilitySelected(int)));
}

const QLinkedList<QString>& MovePatientControl::getPatientsRemoved() const
{
    return _patientsRemoved;
}

const QMap<QString,Patient>& MovePatientControl::getPatientsAdded() const
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
void MovePatientControl::_toFacilityFormPatientMoved(int index)
{
    QString patientHCN;
    if (_toFacilityForm->getCurrentPatient(patientHCN))
    {
	if (_toFacilityForm->getCurrentMoveToIndex() != _tfcurrentFacilityIndex)
	{
	    QMap<int,ID>::const_iterator id =_tfIndexToID.find(index);
	    if (id != _tfIndexToID.end())
	    {
		_facilityMoveToChanges[patientHCN] = id.value();
		_toFacilityForm->removeSelectedPatientItem();
	    }
	}
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

void MovePatientControl::_toBedFormAddPatient()
{
    _addPatientControl->showForm();
}

/**
 * Private slot for when a patient is removed.
 * Checks if the patient was JUST added, if so simply remove it from
 * the list of added patients.
 * If the patient was already there, add them to a list of removed patients
 *
 * Remove the patient from the GUI
 */
void MovePatientControl::_toBedFormRemovePatient()
{
    QString patientHCN;
    if (_toBedForm->getCurrentPatient(patientHCN))
    {
        // See if this patient was also added to the facility
        QMap<QString, Patient>::iterator find = _patientsAdded.find(patientHCN);
        if (find == _patientsAdded.end())
        {
            _patientsRemoved.push_back(patientHCN);
        }
        // If they were, simply remove them from the list of added patients
        else
        {
            _patientsAdded.erase(find);
        }
        _toBedForm->removeSelectedPatientItem();
    }
}

/**
 * When a patient is created, add them to the GUI and list of patients added
 *
 * @param firstName patient's first name
 * @param lastName patient's last name
 * @param hcn the patient's health card number
 * @param requiredCare what kind of care they need
 * @param dateAdded the date added to this facility
 * @param occuringCare the kind of care they are getting
 */
void MovePatientControl::_patientCreated(QString firstName, QString lastName, QString hcn,
                                         QString requiredCare, QDate dateAdded, QString occuringCare)
{
    // Don't add a patient already in the Facility
    if (!_toBedForm->isPatientInList(hcn))
    {
        Patient patient(hcn, firstName, lastName, Convenience::qStringToCareType(requiredCare),
                        Convenience::qStringToCareType(occuringCare), dateAdded);
        _patientsAdded.insert(hcn,patient);
        _toBedForm->addPatientItem(patient.getName(), hcn, occuringCare);
    }
}

void MovePatientControl::_toFacilityFormPatientSelected()
{
    _toFacilityForm->setCurrentMoveToItem(_tfcurrentFacilityIndex);
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

void MovePatientControl::_toFacilityFormFacilitySelected(int index)
{
    _patientsAdded.clear();
    _patientsRemoved.clear();
    _facilityMoveToChanges.clear();
    _toFacilityForm->setCurrentMoveToItem(index);
    QMap<int, ID>::const_iterator find = _tfIndexToID.find(index);
    if (find != _tfIndexToID.end())
    {
	// Store for later
	_tfcurrentFacilityIndex = index;

        if (!_tfWaitingForFacilitiesPatients)
        {
            // If we have the map of facilities to patients
            FacilityIDToPatientInfo::const_iterator fInfo = _tfFacilityToPatientsInfo.find(find.value());
            if (fInfo != _tfFacilityToPatientsInfo.end())
            {
                _toFacilityForm->setPatientItems(fInfo.value());
            }
            else
            {
		//Logger::errorMessage()
                /// @todo log this I guess
            }
        }
    }
    else
    {
        /// @todo log this I guess
    }
}

void MovePatientControl::_toBedFormFacilitySelected(int index)
{
    _bedMoveToChanges.clear();
    QMap<int, ID>::const_iterator find = _tbIndexToID.find(index);
    if (find != _tbIndexToID.end())
    {
        if (!_tbWaitingForFacilitiesPatients)
        {
            // If we have the map of facilities to patients
            FacilityIDToPatientInfo::const_iterator fInfo = _tbFacilityToPatientsInfo.find(find.value());
            if (fInfo != _tbFacilityToPatientsInfo.end())
            {
                _toBedForm->setPatientItems(fInfo.value(), true);
            }
	    else
	    {

	    }
        }
        else
        {
            // Don't have the list of patients yet, store for when we get it
            _tbcurrentFacilityIndex = index;
        }
    }
    else
    {
        /// @todo log this I guess
    }
}
