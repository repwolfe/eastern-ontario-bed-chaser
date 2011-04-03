#ifndef MOVEPATIENTCONTROL_H
#define MOVEPATIENTCONTROL_H

#include "movepatientform.h"
#include "addpatientcontrol.h"
#include "patient.h"

#include <QMap>
#include <QLinkedList>

typedef QMap<ID, QMap<QString, QPair<QString, QString> > > FacilityIDToPatientInfo;
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

    void setFacilitiesList(const QMap<ID, QString>& data);
    void setFacilitiesToPatients(const QMap<ID, QLinkedList<Patient*> >& data);
    void setPatientToBedMap(QMap<QString,QString>& inMap);

    const QMap<QString, QString>& getBedChanges() const;
    const QMap<QString, ID>& getFacilityChanges() const;

    const QLinkedList<QString>& getPatientsRemoved() const;
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

    QLinkedList<QString> _patientsRemoved;
    QMap<QString,Patient> _patientsAdded;

    /// A Map of all the changes done to each Patient for the Bed Form
    QMap<QString, QString> _bedMoveToChanges;

    /// A Map of all the changes done to each Patient for the Facility Form
    QMap<QString, ID> _facilityMoveToChanges;

    /// A map of all the Patients to which Beds they're in
    QMap<QString, QString> _patientToBed;

    // Facility Selection

    // To Facility Form
    QMap<int, ID>       _tfIndexToID;
    int                 _tfcurrentFacilityIndex;
    FacilityIDToPatientInfo _tfFacilityToPatientsInfo;

    // To Bed Form
    QMap<int, ID>       _tbIndexToID;
    int                 _tbcurrentFacilityIndex;
    //QMap<ID, QLinkedList<Patient*> > _tbFacilitiesPatients;
    FacilityIDToPatientInfo _tbFacilityToPatientsInfo;

    // Waiting for information bools
    bool _tfWaitingForFacilitiesList;
    bool _tfWaitingForFacilitiesPatients;

    bool _tbWaitingForFacilitiesList;
    bool _tbWaitingForFacilitiesPatients;
};

#endif // MOVEPATIENTCONTROL_H
