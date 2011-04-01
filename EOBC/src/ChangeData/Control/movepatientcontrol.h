#ifndef MOVEPATIENTCONTROL_H
#define MOVEPATIENTCONTROL_H

#include "movepatientform.h"
#include "addpatientcontrol.h"
#include "patient.h"

#include <QMap>
#include <QLinkedList>

/**
 * @brief Controller for the MovePatientForm for Bed and Facility movement.
 *
 * Handles changes and submissions, and populates the forms with data.
 *
 * @todo Handle changing facility
 * @todo Know what beds are available to move to?
 * @todo Traceability
 */
class MovePatientControl : public QObject
{
    Q_OBJECT
public:
    MovePatientControl();
    ~MovePatientControl();

    void showToFacilityForm();
    void showToBedForm();

    void setFacilitiesList(const QMap<ID, QString>& data);
    void setFacilitiesToPatients(const QMap<ID, QLinkedList<Patient*> >& data);
    void setPatientToBedMap(QMap<QString,QString>& inMap);

    const QMap<QString, QString>& getBedChanges() const;
    const QMap<QString, QString>& getFacilityChanges() const;

    const QLinkedList<QString>& getPatientsRemoved() const;
    const QLinkedList<Patient>& getPatientsAdded() const;

signals:
    void toBedFormSubmitClicked();
    void toFacilityFormSubmitClicked();

private slots:
    void _toFacilityFormPatientMoved(QString moveTo);
    void _toBedFormPatientMoved(QString moveTo);
    void _toBedFormPatientSelected(QString item);
    void _toBedFormSubmit();
    void _toBedFormCancel();
    void _toFacilityFormAddPatient();
    void _toFacilityFormRemovePatient();
    void _patientCreated(QString firstName, QString lastName, QString hcn, QString requiredCare, QDate dateAdded);
    void _toFacilityFormSubmit();
    void _toFacilityFormCancel();

private:
    void _setupConnections();

    MovePatientForm* _toFacilityForm;
    MovePatientForm* _toBedForm;

    /// Used to open a add patient form when adding a new patient to the waiting list
    AddPatientControl* _addPatientControl;

    QLinkedList<Patient> _patientsAdded;
    QLinkedList<QString> _patientsRemoved;

    /// A Map of all the changes done to each Patient for the Bed Form
    QMap<QString, QString> _bedMoveToChanges;

    /// A Map of all the changes done to each Patient for the Bed Form
    QMap<QString, QString> _facilityMoveToChanges;

    /// A map of all the Patients to which Beds they're in
    QMap<QString, QString> _patientToBed;
};

#endif // MOVEPATIENTCONTROL_H
