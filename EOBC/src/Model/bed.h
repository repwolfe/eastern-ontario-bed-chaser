#ifndef BED_H
#define BED_H

#include "inpatient.h"
#include "modelcommon.h"

/**
 * This class represents a Bed from the database.
 *
 */

class Bed
{
public:
    Bed(CareType caretype);
    Bed(CareType caretype, Inpatient* patient);
    ~Bed();

    void setPatient(Inpatient* patient);

private:
    CareType _careType;
    Inpatient* _patient;
    /// @todo Number???
};

#endif // BED_H
