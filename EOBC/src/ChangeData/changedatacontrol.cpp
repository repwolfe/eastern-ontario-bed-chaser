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
    connect(&_getData, SIGNAL(receivedAllFacilities()), SLOT(receivedAllFacilities()));
    connect(&_getData, SIGNAL(receivedAreasWaitingList()), SLOT(receivedAreasWaitingList()));
    connect(&_getData, SIGNAL(receivedFacilitiesPatients()), SLOT(receivedFacilitiesPatients()));
    connect(&_getData, SIGNAL(receivedFacilitiesCurrentBedNumbers()), SLOT(receivedFacilitiesCurrentBedNumbers()));
    connect(&_getData, SIGNAL(receivedFacilitiesMinimumBedNumbers()), SLOT(receivedFacilitiesMinimumBedNumbers()));
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
    const QMap<QString, QString>& changes = _movePatientControl->getFacilityChanges();
    /// @todo send changes to StorageWrite
    Q_UNUSED(changes);
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
    const QLinkedList<Patient>& patientsAdded = _updateWaitingListControl->getPatientsAdded();
    const QLinkedList<QString>& patientsRemoved = _updateWaitingListControl->getPatientsRemoved();
    Q_UNUSED(patientsAdded);
    Q_UNUSED(patientsRemoved);

    /// @todo send the patientsAdded and patientsRemoved to StorageWrite
}
/*
// Get Data
void ChangeDataControl::requestAllFacilities()
{
    _getData.requestAllFacilities();
}

void ChangeDataControl::requestFacilitiesPatients()
{
    _getData.requestFacilitiesPatients();
}

void ChangeDataControl::requestAreasWaitingList()
{
    _getData.requestAreasWaitingList();
}

void ChangeDataControl::requestFacilitiesCurrentBedNumbers()
{
    _getData.requestFacilitiesCurrentBedNumbers();
}

void ChangeDataControl::requestFacilitiesMinimumBedNumbers()
{
    _getData.requestFacilitiesMinimumBedNumbers();
}
*/
// Received Data
void ChangeDataControl::receivedAllFacilities()
{
    emit receivedAllFacilities(_getData.getAllFacilities());
}

void ChangeDataControl::receivedFacilitiesPatients()
{
    emit receivedFacilitiesPatients(_getData.getFacilitiesPatients());
}

void ChangeDataControl::receivedAreasWaitingList()
{
    emit receivedAreasWaitingList(_getData.getAreasWaitingList());
}

void ChangeDataControl::receivedFacilitiesCurrentBedNumbers()
{
    emit receivedFacilitiesCurrentBedNumbers(_getData.getFacilitiesCurrentBedNumbers());
}

void ChangeDataControl::receivedFacilitiesMinimumBedNumbers()
{
    emit receivedFacilitiesMinimumBedNumbers(_getData.getFacilitiesMinimumBedNumbers());
}
