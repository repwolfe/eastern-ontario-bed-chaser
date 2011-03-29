#include "updatewaitinglistcontrol.h"

UpdateWaitingListControl::UpdateWaitingListControl()
{
    _form = new UpdateWaitingListForm();

    /// @todo remove this:
    QMap<QString, QString> patients;
    patients["Robbie Wolfe"] = "1234-123-123";
    patients["JP Landry"] = "5554-234-123";
    patients["Chuck Norris"] = "1233-323-154";
    patients["Austin Chamney"] = "3211-999-123";
    _form->setPatientItems(patients);

    /// @todo okay to have more than one addpatientControl's?
    _addPatientControl = new AddPatientControl();

    connect(_form, SIGNAL(addPatientClicked()), SLOT(_addPatientClicked()));
    connect(_form, SIGNAL(removePatientClicked()), SLOT(_removePatientClicked()));
    connect(_form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
    connect(_form, SIGNAL(cancelClicked()), SLOT(_cancelClicked()));

    connect(_addPatientControl, SIGNAL(submitClicked(QString,QString,QString,QString)), SLOT(_patientCreated(QString,QString,QString,QString)));
}

UpdateWaitingListControl::~UpdateWaitingListControl()
{
    delete _form;
    delete _addPatientControl;
}

const QLinkedList<QString>& UpdateWaitingListControl::getPatientsRemoved() const
{
    return _patientsRemoved;
}

const QLinkedList<Patient>& UpdateWaitingListControl::getPatientsAdded() const
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

void UpdateWaitingListControl::_removePatientClicked()
{
    QString patient = _form->getCurrentPatient();
    _patientsRemoved.push_back(patient);
    _form->removeSelectedPatientItem();
}

void UpdateWaitingListControl::_patientCreated(QString firstName, QString lastName, QString hcn, QString requiredCare)
{
    // Don't add a patient already in the waiting list
    if (!_form->isPatientInList(hcn))
    {
	Patient patient(hcn, firstName, lastName, Convenience::qstringToCareType(requiredCare));
	patient.setDatePlacedOnWaitingList(QDate::currentDate());
	_patientsAdded.push_back(patient);
	_form->addPatientItem(patient.getName(), hcn);
    }
}
