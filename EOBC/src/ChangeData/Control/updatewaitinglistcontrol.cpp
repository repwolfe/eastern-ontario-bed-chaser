#include "updatewaitinglistcontrol.h"

UpdateWaitingListControl::UpdateWaitingListControl()
{
    _form = new UpdateWaitingListForm();

    /// @todo okay to have more than one addpatientControl's?
    _addPatientControl = new AddPatientControl();

    connect(_form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
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

void UpdateWaitingListControl::_addPatientClicked()
{
    _addPatientControl->showForm();
    connect(_addPatientControl, SIGNAL(submitClicked(QString,QString,QString,QString)), SLOT(_patientCreated(QString,QString,QString,QString)));
}

void UpdateWaitingListControl::_removePatientClicked()
{
    QString patient = _form->getCurrentPatient();
    _patientsRemoved.push_back(patient);
}

void UpdateWaitingListControl::_patientCreated(QString firstName, QString lastName, QString hcn, QString requiredCare)
{
    Patient patient(hcn, firstName, lastName, Convenience::qstringToCareType(requiredCare));
    patient.setDatePlacedOnWaitingList(QDate::currentDate());
    _patientsAdded.push_back(patient);
}
