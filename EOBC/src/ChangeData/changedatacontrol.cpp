#include "changedatacontrol.h"

ChangeDataControl::ChangeDataControl(GetDataChangeDataInterface& getData)
    : _getData(getData)
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
    connect(&_getData, SIGNAL(receivedAllFacilities(QMap<ID,QString>)),
            SLOT(_receivedAllFacilities(QMap<ID,QString>)));
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

void ChangeDataControl::displayMovePatientsToBedForm()
{
    // Request data to populate form
    _getData.requestAllFacilities();
    _getData.requestFacilitiesPatients();
    _movePatientControl->showToBedForm();
}

void ChangeDataControl::displayMovePatientsToFacilityForm()
{
    _getData.requestAllFacilities();
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

void ChangeDataControl::displayUpdateBedsForm()
{
    _getData.requestAllFacilities();
    _getData.requestFacilitiesCurrentBedNumbers();
    _getData.requestFacilitiesMinimumBedNumbers();
    _updateBedsControl->showForm();
}

void ChangeDataControl::displayUpdateWaitingList()
{
    _getData.requestAreasWaitingList();
    _updateWaitingListControl->showForm();
}

void ChangeDataControl::movePatientsToBedSubmitted()
{
    const QMap<QString, QString>& changes = _movePatientControl->getBedChanges();
    /// @todo send changes to StorageWrite
    Q_UNUSED(changes);
}

void ChangeDataControl::movePatientsToFacilitySubmitted()
{
    const QMap<QString, QString>& changes   = _movePatientControl->getFacilityChanges();
    const QMap<QString, Patient>& additions = _movePatientControl->getPatientsAdded();
    const QLinkedList<QString>& removals    = _movePatientControl->getPatientsRemoved();
    /// @todo send changes to StorageWrite
    Q_UNUSED(changes);
    Q_UNUSED(additions);
    Q_UNUSED(removals);
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
void ChangeDataControl::_receivedAllFacilities(const QMap<ID, QString> &data)
{
    _movePatientControl->setFacilitiesList(data);
    _updateBedsControl->setFacilitiesList(data);
    _updateWaitingListControl->setFacilitiesList(data);
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
