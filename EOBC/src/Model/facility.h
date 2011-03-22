#ifndef FACILITY_H
#define FACILITY_H

#include "modelcommon.h"
#include "patient.h"

#include <QHash>
#include <QLinkedList>
#include <QPoint>

typedef QHash<QString, Patient*> PatientContainer;
typedef int ID;

/**
 * Facilities have a collection of Patients, each in a different list
 * depending on their level of care required.
 * Each facility also has a certain number of beds, each of a different type
 *
 * This class is part of the Model subsystem described in D2.
 */
class Facility
{
public:
    Facility(ID facilityId, QString facilityName, int numACBeds, int numCCCBeds, QPoint location);
    virtual ~Facility();

    bool addPatientToBed(Patient* patient, CareType type);
    bool movePatientToBed(QString healthCardNum, CareType type);
    bool movePatientToFacility(QString healthCardNum, Facility* otherFacility, CareType type);
    Patient* getPatient(QString healthCardNum) const;
    PatientContainer* getPatientsForType(CareType type);

    bool removePatient(Patient* patient);
    bool removePatient(QString healthCardNumber);

    bool addBeds(unsigned num, CareType type);
    bool decreaseBeds(unsigned num, CareType type);
    int getNumBeds(CareType type);

    ID getFacilityId() const;
    void setFacilityId(ID theId);

    const QString& getFacilityName() const;
    void setFacilityName(QString& inFacilityName);

    const QPoint& getLocation() const;
    void setLocation(QPoint& location);

protected:
    virtual inline bool _getPointersForType(CareType type, PatientContainer*& container, int*& numBeds);
    Patient* _getPatient(const QString& healthCardNum, PatientContainer*& outContainedIn) const;

    PatientContainer _patientsAC;
    PatientContainer _patientsCCC;

    QLinkedList<PatientContainer*> _patients;

    ID _facilityId;
    QString _facilityName;

    int _numACBeds;
    int _numCCCBeds;
    int _numLTCBeds;

    QPoint _location;

private:
    Facility(const Facility&);	// no implicit copy constructors
};

#endif // FACILITY_H
