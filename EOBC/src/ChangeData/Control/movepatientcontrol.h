#ifndef MOVEPATIENTCONTROL_H
#define MOVEPATIENTCONTROL_H

#include "movepatientform.h"
#include <QObject>
#include <QMap>

class MovePatientControl : public QObject
{
    Q_OBJECT
public:
    MovePatientControl();
    ~MovePatientControl();

    void showToFacilityForm();
    void showToBedForm();

signals:

public slots:
    void toFacilityFormPatientMoved(QString moveTo);
    void toBedFormPatientMoved(QString moveTo);
    void toBedFormPatientSelected();

private:
    void _setupConnections();
    void _patientMoved(QString moveTo, QMap<QString, QString>* moveToMap, MovePatientForm* form);

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
