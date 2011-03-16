#ifndef LTC_FACILITY_H
#define LTC_FACILITY_H

#include "facility.h"

class LTC_Facility : public Facility
{
public:
    LTC_Facility(int numLTCBeds);

private:
    /// @todo "waitingListHome"???
};

#endif // LTC_FACILITY_H
