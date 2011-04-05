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
    connect(_createUserControl, SIGNAL(submitClicked(QString,QString,QString, QString, QString)),
	    SLOT(createUserSubmitted(QString,QString,QString,QString, QString)));
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

void ChangeDataControl::movePatientsToBedSubmitted()
{
    QMap<Patient*, QString>  _toBedChanges = _movePatientControl->getBedChanges();
    QMap<QString, Patient>  _additions = _movePatientControl->getPatientsAdded();
    QLinkedList<QString>    _removals = _movePatientControl->getPatientsRemoved();

    Facility* currentFacility = _movePatientControl->getBedFormCurrentFacility();


    /// @todo send changes to StorageWrite
}

void ChangeDataControl::movePatientsToFacilitySubmitted()
{
    QMap<Patient*, Facility*> toFacilityChanges = _movePatientControl->getFacilityChanges();

    Facility* currentFacility = _movePatientControl->getFacilityFormCurrentFacility();

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

void ChangeDataControl::createUserSubmitted(QString, QString, QString, QString, QString)
{
    /// @todo send the username, password, firstname, lastname and priveledge to StorageWrite
    /// or log on control???
}

void ChangeDataControl::updateBedsSubmitted(QString, int, int, int)
{
    /// @todo send the facility, num ac beds, num ccc beds, num ltc beds to StorageWrite
}

void ChangeDataControl::updateWaitingListSubmitted()
{
    const QMap<QString,Patient>& patientsAdded  = _updateWaitingListControl->getPatientsAdded();
    const QLinkedList<QString>& patientsRemoved = _updateWaitingListControl->getPatientsRemoved();
    Q_UNUSED(patientsAdded);
    Q_UNUSED(patientsRemoved);

    /// @todo send the patientsAdded and patientsRemoved to StorageWrite
}

// Received Data
void ChangeDataControl::_receivedAllFacilityPointers(const QMap<ID, Facility*> &data)
{
    _movePatientControl->setFacilitiesList(data);
    _updateBedsControl->setFacilitiesList(data);
}

void ChangeDataControl::_receivedAllAreas(const QMap<ID, QString> &data)
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

void ChangeDataControl::_sendMoveToBedsUpdate(Facility* fac)
{
    QMap<QString, QString>  _toBedChanges;
    QMap<QString, Patient>  _additions;
    QLinkedList<QString>    _removals;

    QLinkedList<Patient*> adds, removes;
    foreach (Patient patient, _additions)
    {
	adds << &patient;
    }

    foreach (QString hcn, _removals)
    {
	// Create temporary patients
	removes << new Patient(hcn, "", "", EOBC::AC);
    }

    /// @todo figure out remote???
    _sendData.addPatients(true, fac->getAreaThisIsIn(), fac, adds);
    _sendData.deletePatients(true, fac->getAreaThisIsIn(), fac, removes);

    // Clear up temporary patients
    foreach (Patient* p, removes)
    {
	delete p;
    }
}

void ChangeDataControl::_sendMoveToFacilityUpdate(Facility* fac)
{
    QMap<QString, QString>  _toBedChanges;
    QMap<QString, ID>	    _toFacilityChanges;
    QMap<QString, Patient>  _additions;
    QLinkedList<QString>    _removals;
}
