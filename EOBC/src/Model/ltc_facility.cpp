#include "ltc_facility.h"

LTC_Facility::LTC_Facility(ID facilityId, QString& facilityName, int numLTCBeds, QPoint& location)
    : Facility(facilityId, facilityName, 0,0, location)
{
    _numLTCBeds = numLTCBeds;
    _patients.clear();  // remove AC and CCC containers from _patients
    _patients.push_back(&_patientsLTC);
}

/**
 * Internal function used to get pointers of the
 * containers and bed numbers for a particular caretype
 *
 * @param type which CareType to get pointers for
 * @param container out PatientContainer pointer to the container of this caretype
 * @param numBeds out pointer to the number of beds of this caretype
 *
 * @return True if acceptable type passed in, False otherwise
 */
inline bool LTC_Facility::_getPointersForType(CareType type, PatientContainer* &container, int* &numBeds)
{
    container = 0;
    numBeds = 0;

    // Using switch in case LTC's get more bed types
    switch (type)
    {
    case EOBC::LTC:
        container = &_patientsLTC;
        numBeds = &_numLTCBeds;
        break;

    default:
        return false;
    }

    return true;
}
