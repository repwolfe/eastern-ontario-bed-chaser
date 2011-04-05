#ifndef MOVEPATIENTCONTROL_H
#define MOVEPATIENTCONTROL_H

#include "movepatientform.h"
#include "addpatientcontrol.h"
#include "facility.h"

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

    void toFacilityFormWaitingForInfo();
    void showToFacilityForm();
    void toBedFormWaitingForInfo();
    void showToBedForm();

    void setFacilitiesList(const QMap<ID, Facility*>& data);
    void setFacilitiesToPatients(const QMap<ID, QLinkedList<Patient*> >& data);

    const QMap<Patient*, QString>& getBedChanges() const;
    const QMap<Patient*, Facility*>& getFacilityChanges() const;
    Facility* getBedFormCurrentFacility() const;
    Facility* getFacilityFormCurrentFacility() const;

    const QLinkedList<Patient*>& getPatientsRemoved() const;
    const QMap<QString,Patient>& getPatientsAdded() const;

signals:
    void toBedFormSubmitClicked();
    void toFacilityFormSubmitClicked();

private slots:
    void _toBedFormPatientMoved(QString moveTo);
    void _toBedFormPatientSelected(QString item);
    void _toBedFormSubmit();
    void _toBedFormCancel();
    void _toBedFormAddPatient();
    void _toBedFormRemovePatient();
    void _toBedFormFacilitySelected(int);
    void _patientCreated(QString firstName, QString lastName, QString hcn, QString requiredCare, QDate dateAdded, QString occuringCare);

    void _toFacilityFormPatientMoved(int index);
    void _toFacilityFormSubmit();
    void _toFacilityFormCancel();
    void _toFacilityFormPatientSelected();
    void _toFacilityFormFacilitySelected(int);


private:
    void _setupConnections();

    MovePatientForm* _toFacilityForm;
    MovePatientForm* _toBedForm;

    /// Used to open a add patient form when adding a new patient to the waiting list
    AddPatientControl* _addPatientControl;

    QLinkedList<Patient*> _patientsRemoved;
    QMap<QString,Patient> _patientsAdded;

    /// A Map of all the changes done to each Patient for the Bed Form
    QMap<Patient*, QString> _bedMoveToChanges;

    /// A Map of all the changes done to each Patient for the Facility Form
    QMap<Patient*, Facility*> _facilityMoveToChanges;

    /// A map of all the Patients to which Beds they're in
    QMap<QString, QString> _patientToBed;

    // Facility Selection
    QMap<ID, Facility*>	    _tfFacilities;
    QMap<ID, Facility*>	    _tbFacilities;
    // To Facility Form
    QHash<int, ID>	    _tfIndexToID;
    int			    _tfcurrentFacilityIndex;
    QHash<QString, Patient*>    _tfPatients;
    QMap<ID, QLinkedList<Patient*> > _tfFacilitiesToPatients;

    // To Bed Form
    QHash<int, ID>	    _tbIndexToID;
    int			    _tbcurrentFacilityIndex;
    QHash<QString, Patient*>    _tbPatients;
    QMap<ID, QLinkedList<Patient*> > _tbFacilitiesToPatients;

    // Waiting for information bools
    bool _tfWaitingForFacilitiesList;
    bool _tfWaitingForFacilitiesPatients;

    bool _tbWaitingForFacilitiesList;
    bool _tbWaitingForFacilitiesPatients;
};

#endif // MOVEPATIENTCONTROL_H
