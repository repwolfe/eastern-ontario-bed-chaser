#ifndef UPDATEWAITINGLISTCONTROL_H
#define UPDATEWAITINGLISTCONTROL_H

#include <QLinkedList>

#include "updatewaitinglistform.h"
#include "addpatientcontrol.h"
#include "patient.h"
#include "convenience.h"

class UpdateWaitingListControl : public QObject
{
    Q_OBJECT
public:
    UpdateWaitingListControl();
    ~UpdateWaitingListControl();

    void showForm();

    const QLinkedList<QString>& getPatientsRemoved() const;
    const QLinkedList<Patient>& getPatientsAdded() const;

signals:
    void submitClicked();

private slots:
    void _submitClicked();
    void _cancelClicked();
    void _removePatientClicked();
    void _addPatientClicked();
    void _patientCreated(QString firstName, QString lastName, QString hcn, QString requiredCare);

private:
    UpdateWaitingListForm* _form;

    /// Used to open a add patient form when adding a new patient to the waiting list
    AddPatientControl* _addPatientControl;

    QLinkedList<QString> _patientsRemoved;

    /// @todo think of a way not to need patient, might be necessary though
    QLinkedList<Patient> _patientsAdded;

};

#endif // UPDATEWAITINGLISTCONTROL_H
