#ifndef FACILITY_H
#define FACILITY_H

#include "modelcommon.h"
#include "inpatient.h"

#include <QHash>
#include <QLinkedList>

typedef QHash<QString, Inpatient*> PatientContainer;

/**
 * Facilities have a collection of Inpatients, each in a different list
 * depending on their level of care required.
 * Each facility also has a certain number of beds, each of a different type
 *
 * This class is part of the Model subsystem described in D2.
 */
class Facility
{
public:
    Facility(int facilityId, int numACBeds, int numCCCBeds);
    virtual ~Facility();

    bool addPatientToBed(Inpatient* patient, CareType type);
    bool addPatientToBed(QString& healthCardNumber, QString& name, QDate &placedOnWaitingList, QDate& admissionDate, CareType type);
    bool movePatientToBed(QString& healthCardNum, CareType type);
    Inpatient* getInpatient(QString& healthCardNum) const;

    bool removePatient(Inpatient* patient);
    bool removePatient(QString& healthCardNumber);

    void addBeds(unsigned num, CareType type);
    void decreaseBeds(unsigned num, CareType type);
    int getNumBeds(CareType type);

    int getFacilityId() const;

protected:
    virtual inline bool _getPointersForType(CareType type, PatientContainer*& container, int*& numBeds);
    Inpatient* _getInpatient(QString& healthCardNum, PatientContainer*& outContainedIn) const;

    PatientContainer _patientsAC;
    PatientContainer _patientsCCC;

    QLinkedList<PatientContainer*> _patients;

    int _facilityId;

    int _numACBeds;
    int _numCCCBeds;
};

#endif // FACILITY_H
