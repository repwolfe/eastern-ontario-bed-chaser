#ifndef MOVEPATIENTCONTROL_H
#define MOVEPATIENTCONTROL_H

#include "movepatientform.h"
#include "patient.h"

#include <QObject>
#include <QMap>

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

signals:
    void toBedFormSubmitClicked();
    void toFacilityFormSubmitClicked();

public slots:
    void toFacilityFormPatientMoved(QString moveTo);
    void toBedFormPatientMoved(QString moveTo);
    void toBedFormPatientSelected(QString item);
    void toBedFormSubmit();
    void toBedFormCancel();
    void toFacilityFormSubmit();
    void toFacilityFormCancel();

private:
    void _setupConnections();

    MovePatientForm* _toFacilityForm;
    MovePatientForm* _toBedForm;

    /// A Map of all the changes done to each Patient for the Bed Form
    QMap<QString, QString> _bedMoveToChanges;

    /// A Map of all the changes done to each Patient for the Bed Form
    QMap<QString, QString> _facilityMoveToChanges;

    /// A map of all the Patients to which Beds they're in
    QMap<QString, QString> _patientToBed;
};

#endif // MOVEPATIENTCONTROL_H
