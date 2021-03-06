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
void MovePatientControl::setFacilitiesList(const QMap<ID, Facility*>& data)
{
    QStringList facilities;
    QHash<int, ID> indexToFacilityId;
    if (_tfWaitingForFacilitiesList || _tbWaitingForFacilitiesList)
    {
	QMap<ID, Facility*>::const_iterator iter = data.begin();
        int index = 0;
        while (iter != data.end())
        {
	    facilities << iter.value()->getFacilityName();
            indexToFacilityId[index] = iter.key();
            ++index;
            ++iter;
        }
    }

    if (_tfWaitingForFacilitiesList)
    {
        _tfWaitingForFacilitiesList = false;
	_tfFacilities = data;
        _toFacilityForm->setFacilityItems(facilities);
	_toFacilityForm->setMoveToItems(facilities);
        _tfIndexToID = indexToFacilityId;
    }

    if (_tbWaitingForFacilitiesList)
    {
        _tbWaitingForFacilitiesList = false;
	_tbFacilities = data;
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
    QHash<QString, Patient*> patients;
    // If either form needs it, generate new map
    if (_tfWaitingForFacilitiesPatients || _tbWaitingForFacilitiesPatients)
    {
        QMap<ID, QLinkedList<Patient*> >::const_iterator iter = data.begin();
        while (iter != data.end())
        {
            foreach (Patient* patient, iter.value())
            {
		patients[patient->getHealthCardNumber()] = patient;
	    }
            ++iter;
        }
    }

    if (_tfWaitingForFacilitiesPatients)
    {
        _tfWaitingForFacilitiesPatients = false;
	_tfPatients = patients;
	_tfFacilitiesToPatients = data;

        // If we have the patient info now and finished waiting for facilities, populate form
        if (!_tfWaitingForFacilitiesList)
        {
            _toFacilityFormFacilitySelected(_tfcurrentFacilityIndex);
        }
    }

    if (_tbWaitingForFacilitiesPatients)
    {
        _tbWaitingForFacilitiesPatients = false;
	_tbPatients = patients;
	_tbFacilitiesToPatients = data;

        // If we have the patient info now and finished waiting for facilities, populate form
        if (!_tbWaitingForFacilitiesList)
        {
            _toBedFormFacilitySelected(_tbcurrentFacilityIndex);
        }
    }
}

const QMap<Patient*, QString>& MovePatientControl::getBedChanges() const
{
    return _bedMoveToChanges;
}
const QMap<Facility*, QLinkedList<Patient*> >& MovePatientControl::getFacilityChanges() const
{
    return _facilityMoveToChanges;
}

const QLinkedList<Patient*>& MovePatientControl::getFacilityMoveToPatientsRemoved() const
{
    return _facilityMoveToPatientsRemoved;
}

/**
 * Returns the currently selected Facility based off the index of the combobox
 *
 * @return currently selected Facility, or 0
 */
Facility* MovePatientControl::getBedFormCurrentFacility() const
{
    QHash<int, ID>::const_iterator id = _tbIndexToID.find(_tbcurrentFacilityIndex);
    if (id != _tbIndexToID.end())
    {
	QMap<ID, Facility*>::const_iterator fac = _tbFacilities.find(id.value());
	if (fac != _tbFacilities.end())
	{
	    return fac.value();
	}
    }
    return 0;
}

/**
 * Returns the currently selected facility id based off the index of the combobox
 *
 * @return currently selected facility id, or 0
 */
Facility* MovePatientControl::getFacilityFormCurrentFacility() const
{
    QHash<int, ID>::const_iterator id = _tfIndexToID.find(_tfcurrentFacilityIndex);
    if (id != _tbIndexToID.end())
    {
	QMap<ID, Facility*>::const_iterator fac = _tfFacilities.find(id.value());
	if (fac != _tfFacilities.end())
	{
	    return fac.value();
	}
    }
    return 0;
}

/**
 * Used to indicate that this form is waiting for data
 */
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
}

/**
 * Used to indicate that this form is waiting for data
 */
void MovePatientControl::toBedFormWaitingForInfo()
{
    _tbWaitingForFacilitiesList = true;
    _tbWaitingForFacilitiesPatients = true;
}

void MovePatientControl::showToBedForm()
{
    _bedMoveToChanges.clear();
    _toBedForm->show();
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

const QLinkedList<Patient*>& MovePatientControl::getPatientsRemoved() const
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
 * anywhere, the change stored in the map. Also remove them from the GUI
 *
 * @param int the index of the facility they are moved to
 */
void MovePatientControl::_toFacilityFormPatientMoved(int index)
{
    QString patientHCN;
    if (_toFacilityForm->getCurrentPatient(patientHCN))
    {
	if (_toFacilityForm->getCurrentMoveToIndex() != _tfcurrentFacilityIndex)
	{
	    // Get the ID of the Facility they were moved to
	    QHash<int,ID>::const_iterator newFacId =_tfIndexToID.find(index);
	    if (newFacId != _tfIndexToID.end())
	    {
		// Find the Patient* for who was moved
		QHash<QString, Patient*>::const_iterator p = _tfPatients.find(patientHCN);
		if (p != _tfPatients.end())
		{
		    // Find the Facility* for where they were moved
		    QMap<ID, Facility*>::const_iterator fac = _tfFacilities.find(newFacId.value());
		    if (fac != _tfFacilities.end())
		    {
			_facilityMoveToChanges[fac.value()] << p.value();
			_facilityMoveToPatientsRemoved << p.value();
			_toFacilityForm->removeSelectedPatientItem();
		    }
		}
	    }
	}
    }
}

/**
 * Everytime a patient with a specific health card number is moved
 * anywhere, the change stored in the map.
 *
 * @param moveTo where they were moved
 */
void MovePatientControl::_toBedFormPatientMoved(QString moveTo)
{
    QString patientHCN;
    if (_toBedForm->getCurrentPatient(patientHCN))
    {
	QMap<QString,QString>::const_iterator bed = _patientToBed.find(patientHCN);
	if (bed != _patientToBed.end())
	{
	    QHash<QString, Patient*>::const_iterator patient = _tbPatients.find(patientHCN);
	    if (patient != _tbPatients.end())
	    {
		// Avoid redundant changes (bed == AC, bed --> CCC, bed --> AC)
		if (bed.value() != moveTo)
		{
		    _bedMoveToChanges[patient.value()] = moveTo;
		}
		else
		{
		    // Moved from original bed to something else back to original
		    // remove the change since it will be redundant
		    _bedMoveToChanges.remove(patient.value());
		}
	    }
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
	    QHash<QString, Patient*>::const_iterator patient = _tbPatients.find(patientHCN);
	    if (patient != _tbPatients.end())
	    {
		_patientsRemoved.push_back(patient.value());
	    }
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

/**
 * When a facility is selected from the drop down box, find out
 * its ID then use that to get the list of patients associated
 * with that facility.
 */
void MovePatientControl::_toFacilityFormFacilitySelected(int index)
{
    _facilityMoveToChanges.clear();
    _facilityMoveToPatientsRemoved.clear();
    _toFacilityForm->setCurrentMoveToItem(index);
    QHash<int, ID>::const_iterator find = _tfIndexToID.find(index);
    if (find != _tfIndexToID.end())
    {
	// Store for later
	_tfcurrentFacilityIndex = index;

        if (!_tfWaitingForFacilitiesPatients)
        {
            // If we have the map of facilities to patients
	    QMap<ID, QLinkedList<Patient*> >::const_iterator fPatients = _tfFacilitiesToPatients.find(find.value());
	    if (fPatients != _tfFacilitiesToPatients.end())
            {
		_toFacilityForm->setPatientItems(fPatients.value());
            }
            else
            {
		Logger::errorMessage("MovePatientControl", "_toFacilityformFacilitySelected(int)", "Couldn't find facility with ID", QString::number(find.value()));
            }
        }
    }
    else
    {
	Logger::errorMessage("MovePatientControl", "_toFacilityformFacilitySelected(int)", "Couldn't find facility with index", QString::number(index));
    }
}

/**
 * When a facility is selected from the drop down box, find out
 * its ID then use that to get the list of patients associated
 * with that facility.
 *
 * Slightly simpler implementation than for to facility form
 */
void MovePatientControl::_toBedFormFacilitySelected(int index)
{
    _patientsAdded.clear();
    _patientsRemoved.clear();
    _bedMoveToChanges.clear();
    QHash<int, ID>::const_iterator find = _tbIndexToID.find(index);
    if (find != _tbIndexToID.end())
    {
	// Store for later
	_tbcurrentFacilityIndex = index;

        if (!_tbWaitingForFacilitiesPatients)
        {
            // If we have the map of facilities to patients
	    QMap<ID, QLinkedList<Patient*> >::const_iterator fPatients = _tbFacilitiesToPatients.find(find.value());
	    if (fPatients != _tbFacilitiesToPatients.end())
            {
		_toBedForm->setPatientItems(fPatients.value(), true);
            }
	    else
	    {
		Logger::errorMessage("MovePatientControl", "_toBedFormFacilitySelected(int)", "Couldn't find facility with ID", QString::number(find.value()));
	    }
        }
    }
    else
    {
	Logger::errorMessage("MovePatientControl", "_toBedFormFacilitySelected(int)", "Couldn't find facility with index", QString::number(index));
    }
}
