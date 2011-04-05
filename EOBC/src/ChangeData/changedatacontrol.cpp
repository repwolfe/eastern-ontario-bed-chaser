#include "changedatacontrol.h"

ChangeDataControl::ChangeDataControl(GetDataChangeDataInterface &getData, SendChangeDataInterface &sendData)
    : _getData(getData), _sendData(sendData)
{
    _movePatientControl		= new MovePatientControl();
    _addFacilityControl		= new AddFacilityControl();
    _createUserControl		= new CreateUserControl();
    _updateBedsControl		= new UpdateBedsControl();
    _updateWaitingListControl	= new UpdateWaitingListControl();

    _setupConnections();
}

ChangeDataControl::~ChangeDataControl()
{
    delete _movePatientControl;
    delete _addFacilityControl;
    delete _createUserControl;
    delete _updateBedsControl;
    delete _updateWaitingListControl;
}

void ChangeDataControl::_setupConnections()
{
    connect(_movePatientControl, SIGNAL(toBedFormSubmitClicked()), SLOT(movePatientsToBedSubmitted()));
    connect(_movePatientControl, SIGNAL(toFacilityFormSubmitClicked()), SLOT(movePatientsToFacilitySubmitted()));
    connect(_addFacilityControl, SIGNAL(submitClicked(QString,QString,QString)),
	    SLOT(addFacilitySubmitted(QString,QString,QString)));
    connect(_createUserControl, SIGNAL(submitClicked(QString,QString,QString)),
	    SLOT(createUserSubmitted(QString,QString,QString)));
    connect(_updateWaitingListControl, SIGNAL(submitClicked()), SLOT(updateWaitingListSubmitted()));

    // GetData
    connect(&_getData, SIGNAL(receivedAllFacilityPointers(QMap<ID,Facility*>)),
	    SLOT(_receivedAllFacilityPointers(QMap<ID,Facility*>)));
    connect(&_getData, SIGNAL(receivedAllAreas(QMap<ID,QString>)),
	    SLOT(_receivedAllAreas(QMap<ID,QString>)));
    connect(&_getData, SIGNAL(receivedAreasWaitingList(QMap<ID,QLinkedList<Patient*> >)),
            SLOT(_receivedAreasWaitingList(QMap<ID,QLinkedList<Patient*> >)));
    connect(&_getData, SIGNAL(receivedFacilitiesPatients(QMap<ID,QLinkedList<Patient*> >)),
            SLOT(_receivedFacilitiesPatients(QMap<ID,QLinkedList<Patient*> >)));
    connect(&_getData, SIGNAL(receivedFacilitiesCurrentBedNumbers(QMap<ID,QVector<int> >)),
            SLOT(_receivedFacilitiesCurrentBedNumbers(QMap<ID,QVector<int> >)));
    connect(&_getData, SIGNAL(receivedFacilitiesMinimumBedNumbers(QMap<ID,QVector<int> >)),
	    SLOT(_receivedFacilitiesMinimumBedNumbers(QMap<ID,QVector<int> >)));
}

/// @todo implement this
bool ChangeDataControl::changeData(QString &args, QString &data)
{
    return true;
}

/****************************************
 *                SLOTS                 *
 ****************************************/

/**
 * Requests data for the form and then displays it
 */
void ChangeDataControl::displayMovePatientsToBedForm()
{
    _movePatientControl->toBedFormWaitingForInfo();
    _getData.requestAllFacilityPointers();
    _getData.requestFacilitiesPatients();
    _movePatientControl->showToBedForm();
}

/**
 * Requests data for the form and then displays it
 */
void ChangeDataControl::displayMovePatientsToFacilityForm()
{
    _movePatientControl->toFacilityFormWaitingForInfo();
    _getData.requestAllFacilityPointers();
    _getData.requestFacilitiesPatients();
    _movePatientControl->showToFacilityForm();
}

void ChangeDataControl::displayAddFacilityForm()
{
    _addFacilityControl->showForm();
}

void ChangeDataControl::displayCreateUserForm()
{
    _createUserControl->showForm();
}

/**
 * Requests data for the form and then displays it
 */
void ChangeDataControl::displayUpdateBedsForm()
{
    _updateBedsControl->waitingForData();
    _getData.requestAllFacilityPointers();
    _getData.requestFacilitiesCurrentBedNumbers();
    _getData.requestFacilitiesMinimumBedNumbers();
    _updateBedsControl->showForm();
}

/**
 * Requests data for the form and then displays it
 */
void ChangeDataControl::displayUpdateWaitingList()
{
    _updateWaitingListControl->waitingForData();
    _getData.requestAllAreas();
    _getData.requestAreasWaitingList();
    _updateWaitingListControl->showForm();
}

/**
 * When the Move patient to bed form is submitted,
 * all the changes is stored in the database and
 * sent to all other systems.
 * -All new patients are added
 * -All removed patients are removed
 * -All moved patients are first removed, then readded with the new bed
 *  (as per the communication protocol)
 */
void ChangeDataControl::movePatientsToBedSubmitted()
{
    QMap<Patient*, QString>  toBedChanges = _movePatientControl->getBedChanges();
    QMap<QString, Patient>  additions = _movePatientControl->getPatientsAdded();
    QLinkedList<Patient*>   removals = _movePatientControl->getPatientsRemoved();
    Facility* currentFacility = _movePatientControl->getBedFormCurrentFacility();

    QLinkedList<Patient*> adds, adds2, removes;
    QMap<QString, Patient>::iterator patient = additions.begin();
    while (patient != additions.end())
    {
	adds << &patient.value();
	++patient;
    }

    QMap<Patient*,QString>::const_iterator bedChanges = toBedChanges.begin();
    while (bedChanges != toBedChanges.end())
    {
	removes << bedChanges.key();
	Patient* newPatient = bedChanges.key();
	newPatient->setOccupiedCare(Convenience::qStringToCareType(bedChanges.value()));
	adds2 << newPatient;
	++bedChanges;
    }

    /// @todo figure out remote???
    if (!adds.empty()) { _sendData.addPatients(true, currentFacility->getAreaThisIsIn(), currentFacility, adds); }
    if (!removals.empty()) { _sendData.deletePatients(true, currentFacility->getAreaThisIsIn(), currentFacility, removals); }
    if (!adds2.empty()) { _sendData.addPatients(true, currentFacility->getAreaThisIsIn(), currentFacility, adds2); }
    if (!removes.empty()) { _sendData.deletePatients(true, currentFacility->getAreaThisIsIn(), currentFacility, removes); }

    /// @todo send changes to StorageWrite
}

/**
 * When the Move patient to facility form is submitted,
 * all the changes is stored in the database and
 * sent to all other systems.
 * -All moved patients are first removed, then readded to the new Facility
 *  (as per the communication protocol)
 */
void ChangeDataControl::movePatientsToFacilitySubmitted()
{
    QMap<Facility*, QLinkedList<Patient*> > toFacilityChanges = _movePatientControl->getFacilityChanges();
    QLinkedList<Patient*> patientsRemoved = _movePatientControl->getFacilityMoveToPatientsRemoved();

    Facility* currentFacility = _movePatientControl->getFacilityFormCurrentFacility();

    /// @todo figure out remote???
    if (!patientsRemoved.empty())
    {
	_sendData.deletePatients(true, currentFacility->getAreaThisIsIn(), currentFacility, patientsRemoved);

	// If patientsRemoved is empty, this doesn't need to happen
	QMap<Facility*, QLinkedList<Patient*> >::const_iterator patients = toFacilityChanges.begin();
	while (patients != toFacilityChanges.end())
	{
	    if (!patients.value().empty())
	    {
		_sendData.addPatients(true, patients.key()->getAreaThisIsIn(), patients.key(), patients.value());
	    }
	    ++patients;
	}
    }

    /// @todo send changes to StorageWrite
}

void ChangeDataControl::addFacilitySubmitted(QString, QString, QString)
{
    /// @todo send the facilityname, x-axis and y-axis to StorageWrite
}

void ChangeDataControl::addPatientSubmitted(QString, QString, QString, QString)
{
    /// @todo send the firstname, lastname, healthcardnum and required care to StorageWrite
}

void ChangeDataControl::createUserSubmitted(QString, QString, QString)
{
    /// @todo send the username, password, and priveledge to StorageWrite
    /// or log on control???
}

void ChangeDataControl::updateBedsSubmitted(QString, int, int, int)
{
    /// @todo send the facility, num ac beds, num ccc beds, num ltc beds to StorageWrite
}

void ChangeDataControl::updateWaitingListSubmitted()
{
    QMap<QString,Patient> patientsAdded  = _updateWaitingListControl->getPatientsAdded();
    QLinkedList<Patient*> removes = _updateWaitingListControl->getPatientsRemoved();

    QLinkedList<Patient*> adds;

    QMap<QString, Patient>::iterator patient = patientsAdded.begin();
    while (patient != patientsAdded.end())
    {
	adds << &patient.value();
	++patient;
    }

    /// @todo figure out remote
    if (!adds.empty()) { _sendData.addPatients(true, (Area*)0, adds); }
    if (!removes.empty()) { _sendData.deletePatients(true, (Area*)0, (Facility*)0, removes); }

    /// @todo send the patientsAdded and patientsRemoved to StorageWrite
}

// Received Data
void ChangeDataControl::_receivedAllFacilityPointers(const QMap<ID, Facility*> &data)
{
    _movePatientControl->setFacilitiesList(data);
    _updateBedsControl->setFacilitiesList(data);
}

void ChangeDataControl::_receivedAllAreas(const QMap<ID, Area*> &data)
{
    _updateWaitingListControl->setAreasList(data);
}

void ChangeDataControl::_receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient *> > &data)
{
    _movePatientControl->setFacilitiesToPatients(data);
}

void ChangeDataControl::_receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient *> > &data)
{
    _updateWaitingListControl->setAreasWaitingList(data);
}

void ChangeDataControl::_receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> > &data)
{
    _updateBedsControl->setCurrentBedNumbers(data);
}

void ChangeDataControl::_receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> > &data)
{
    _updateBedsControl->setMinimumBedNumbers(data);
}

void ChangeDataControl::_sendMoveToFacilityUpdate(Facility* fac)
{
    QMap<QString, QString>  _toBedChanges;
    QMap<QString, ID>	    _toFacilityChanges;
    QMap<QString, Patient>  _additions;
    QLinkedList<QString>    _removals;
}
