#ifndef UPDATEWAITINGLISTCONTROL_H
#define UPDATEWAITINGLISTCONTROL_H

#include <QLinkedList>

#include "updatewaitinglistform.h"
#include "addpatientcontrol.h"
#include "patient.h"
#include "convenience.h"

/**
 * @brief Controller for UpdateWaitingListForm.
 *
 * Allows you to add a Patient to a Waiting List, using
 * the AddPatientControl and AddPatientForm.
 * Also allows you to remove a Patient from a waiting list.
 *
 * @todo Traceability
 */
class UpdateWaitingListControl : public QObject
{
    Q_OBJECT
public:
    UpdateWaitingListControl();
    ~UpdateWaitingListControl();

    void showForm();

    void setFacilitiesList(const QMap<ID, QString>& data);
    void setAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >& data);

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
