#ifndef FACILITY_H
#define FACILITY_H

#include "modelcommon.h"
#include "inpatient.h"

#include <QHash>

/**
 * Facilities have a collection of Inpatients, each in a different list
 * depending on their level of care required.
 * Each facility also has a certain number of beds, each of a different type
 */
class Facility
{
public:
    Facility();
    ~Facility();

private:
    /// @todo Think about LTC facilities (which only have one hash) (maybe remove it)
    QHash<int, Inpatient*> _patientsAC;
    QHash<int, Inpatient*> _patientsCCC;
    QHash<int, Inpatient*> _patientsLTC;

    int _numACBeds;
    int _numCCCBeds;
    int _numLTCBeds;
};

#endif // FACILITY_H
