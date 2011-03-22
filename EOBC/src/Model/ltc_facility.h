#ifndef LTC_FACILITY_H
#define LTC_FACILITY_H

#include "facility.h"

class LTC_Facility : public Facility
{
public:
    LTC_Facility(ID facilityId, QString& facilityName, int numLTCBeds, QPoint& location);

protected:
    virtual inline bool _getPointersForType(CareType type, PatientContainer* &container, int* &numBeds);

private:
    /// @todo "waitingListHome"???

    PatientContainer _patientsLTC;
};

#endif // LTC_FACILITY_H
