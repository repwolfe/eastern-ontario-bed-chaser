#ifndef UPDATEWAITINGLISTCONTROL_H
#define UPDATEWAITINGLISTCONTROL_H

#include <QLinkedList>

#include "updatewaitinglistform.h"
#include "addpatientcontrol.h"
#include "area.h"
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
    void waitingForData();

    void setAreasList(const QMap<ID, Area*>& data);
    void setAreasWaitingList(const QMap<ID, QLinkedList<Patient*> >& data);

    const QLinkedList<Patient*>& getPatientsRemoved() const;
    const QMap<QString, Patient>& getPatientsAdded() const;
    Area* getCurrentlySelectedArea() const;

signals:
    void submitClicked();

private slots:
    void _submitClicked();
    void _cancelClicked();
    void _removePatientClicked();
    void _addPatientClicked();
    void _patientCreated(QString firstName, QString lastName, QString hcn, QString requiredCare, QDate dateAdded);
    void _areaSelected(int index);

private:
    UpdateWaitingListForm* _form;

    bool _waitingForAreasList;
    bool _waitingForWaitingList;
    int _currentAreaIndex;

    QHash<int, Area*> _indexToArea;
    QMap<ID, QLinkedList<Patient*> > _areaToPatients;
    QHash<QString, Patient*> _patients;

    /// Used to open a add patient form when adding a new patient to the waiting list
    AddPatientControl* _addPatientControl;

    QLinkedList<Patient*> _patientsRemoved;

    QMap<QString, Patient> _patientsAdded;

};

#endif // UPDATEWAITINGLISTCONTROL_H
