#include "getdatareceiveinterface.h"

GetDataReceiveInterface::GetDataReceiveInterface(GetDataControl &getData) :
    _getData(getData)
{
    connect(&_getData, SIGNAL(receivedFacilityRequest()),
            SLOT(_receivedFacilityRequest()));
}

/**
 * Slot for when a specific Facility was updated
 * @param fac Facility that was updated
 */
void GetDataReceiveInterface::_receivedFacilityRequest()
{
    _getData.receivedFacilityRequest();
}


