#include "updatewaitinglistcontrol.h"

UpdateWaitingListControl::UpdateWaitingListControl()
{
    _form = new UpdateWaitingListForm();

    _waitingForAreasList = false;
    _waitingForWaitingList = false;
    _currentAreaIndex = 0;

    _addPatientControl = new AddPatientControl(false);

    connect(_form, SIGNAL(addPatientClicked()), SLOT(_addPatientClicked()));
    connect(_form, SIGNAL(removePatientClicked()), SLOT(_removePatientClicked()));
    connect(_form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
    connect(_form, SIGNAL(cancelClicked()), SLOT(_cancelClicked()));
    connect(_form, SIGNAL(areaSelected(int)), SLOT(_areaSelected(int)));

    connect(_addPatientControl, SIGNAL(submitClicked(QString,QString,QString,QString,QDate)), SLOT(_patientCreated(QString,QString,QString,QString,QDate)));
}

UpdateWaitingListControl::~UpdateWaitingListControl()
{
    delete _form;
    delete _addPatientControl;
}

void UpdateWaitingListControl::waitingForData()
{
    _waitingForAreasList = true;
    _waitingForWaitingList = true;
}

void UpdateWaitingListControl::setAreasList(const QMap<ID, QString>& data)
{
    QStringList areas;

    if (_waitingForAreasList)
    {
	_waitingForAreasList = false;
	QMap<ID, QString>::const_iterator iter = data.begin();
	int index = 0;
	while (iter != data.end())
	{
	    areas << iter.value();
	    _indexToAreaId[index] = iter.key();
	    ++index;
	    ++iter;
	}
	_form->setAreaItems(areas);
    }
}

void UpdateWaitingListControl::setAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >& data)
{
    if (_waitingForWaitingList)
    {
	_waitingForWaitingList = false;
	_areaToPatientInfo.clear();
	QMap<ID, QLinkedList<Patient*> >::const_iterator iter = data.begin();
	while (iter != data.end())
	{
	    QHash<QString,QString> patientInfo;
	    const QLinkedList<Patient*>& patients = iter.value();
	    foreach (Patient* patient, patients)
	    {
		patientInfo[patient->getHealthCardNumber()] = patient->getName();
	    }
	    _areaToPatientInfo[iter.key()] = patientInfo;
	    ++iter;
	}
	if (!_waitingForAreasList)
	{
	    _areaSelected(_currentAreaIndex);
	}
    }
}

const QLinkedList<QString>& UpdateWaitingListControl::getPatientsRemoved() const
{
    return _patientsRemoved;
}

const QMap<QString,Patient>& UpdateWaitingListControl::getPatientsAdded() const
{
    return _patientsAdded;
}

void UpdateWaitingListControl::showForm()
{
    /// @todo populate with real data! :)
    _form->show();
}

/****************************************
 *                SLOTS                 *
 ****************************************/
void UpdateWaitingListControl::_submitClicked()
{
    emit submitClicked();
    _form->close();
}

void UpdateWaitingListControl::_cancelClicked()
{
    _form->close();
    _patientsRemoved.clear();
    _patientsAdded.clear();
}

void UpdateWaitingListControl::_addPatientClicked()
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
void UpdateWaitingListControl::_removePatientClicked()
{
    QString patientHCN;
    if (_form->getCurrentPatient(patientHCN))
    {
        // See if this patient was also added to the waiting list
        QMap<QString, Patient>::iterator find = _patientsAdded.find(patientHCN);
        if (find == _patientsAdded.end())
        {
            _patientsRemoved.push_back(patientHCN);
            _form->removeSelectedPatientItem();
        }
        // If they were, simply remove them from the list of added patients
        else
        {
            _patientsAdded.erase(find);
        }
    }
}

/**
 * When a patient is created, add them to the GUI and list of patients added
 *
 * @param firstName patient's first name
 * @param lastName patient's last name
 * @param hcn the patient's health card number
 * @param requiredCare what kind of care they need
 * @param dateAdded the date added to this waiting list
 */
void UpdateWaitingListControl::_patientCreated(QString firstName, QString lastName, QString hcn, QString requiredCare, QDate dateAdded)
{
    // Don't add a patient already in the waiting list
    if (!_form->isPatientInList(hcn))
    {
	Patient patient(hcn, firstName, lastName, Convenience::qStringToCareType(requiredCare), dateAdded);
        _patientsAdded.insert(hcn,patient);
	_form->addPatientItem(patient.getName(), hcn);
    }
}

/**
 * When a Area is selected from the drop down box, find out
 * its ID then use that to get the list of patients associated
 * with that Area's waiting list.
 */
void UpdateWaitingListControl::_areaSelected(int index)
{
    _patientsAdded.clear();
    _patientsRemoved.clear();
    QMap<int, ID>::const_iterator find = _indexToAreaId.find(index);
    if (find != _indexToAreaId.end())
    {
	_currentAreaIndex = index;
	if (!_waitingForAreasList)
	{
	    // If we have the map of Areas to patients
	    QMap<ID, QHash<QString,QString> >::const_iterator pInfo = _areaToPatientInfo.find(find.value());
	    if (pInfo != _areaToPatientInfo.end())
	    {
		_form->setPatientItems(pInfo.value());
	    }
	    else
	    {
		Logger::errorMessage("UpdateWaitingListControl", "_areaSelected(int)", "Couldn't find Area with ID", QString::number(find.value()));
	    }
	}
    }
    else
    {
	Logger::errorMessage("UpdateWaitingListControl", "_areaSelected(int)", "Couldn't find Area with index", QString::number(index));
    }
}
