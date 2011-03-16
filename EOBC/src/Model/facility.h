#ifndef FACILITY_H
#define FACILITY_H

#include "modelcommon.h"
#include "inpatient.h"

#include <QHash>
#include <QLinkedList>

/**
 * Facilities have a collection of Inpatients, each in a different list
 * depending on their level of care required.
 * Each facility also has a certain number of beds, each of a different type
 */

typedef QHash<QString, Inpatient*> PatientContainer;

class Facility
{
public:
    Facility(int numACBeds, int numCCCBeds);
    ~Facility();

    bool addPatientToBed(Inpatient* patient, CareType type);
    bool addPatientToBed(QString& healthCardNumber, QString& name, QDate &placedOnWaitingList, QDate& admissionDate, CareType type);
    bool movePatientToBed(QString& healthCardNum, CareType type);
    Inpatient* getInpatient(QString& healthCardNum);

    bool removePatient(Inpatient* patient);
    bool removePatient(QString& healthCardNumber);

    void addBeds(unsigned num, CareType type);
    void decreaseBeds(unsigned num, CareType type);
    int getNumBeds(CareType type);

private:
    inline void _getPointersForType(CareType type, PatientContainer*& container, int*& numBeds);
    Inpatient* _getInpatient(QString& healthCardNum, PatientContainer*& outContainedIn);

    /// @todo Think about LTC facilities (which only have one hash) (maybe remove it)
    PatientContainer _patientsAC;
    PatientContainer _patientsCCC;
 //   PatientContainer _patientsLTC;

    QLinkedList<PatientContainer*> _patients;

    int _numACBeds;
    int _numCCCBeds;
 //   int _numLTCBeds;
};

#endif // FACILITY_H
