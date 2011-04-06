#include "getdatadisplaymapinterface.h"

GetDataDisplayMapInterface::GetDataDisplayMapInterface(GetDataControl &getData) :
    _getData(getData)
{
    connect(&_getData, SIGNAL(receivedUpdatedFacility(Facility*,bool)),
            SLOT(_receivedUpdatedFacility(Facility*)));
    connect(&_getData, SIGNAL(receivedUpdatedWaitingList(ID,WaitingList&)),
            SLOT(_receivedUpdatedWaitingList(ID,WaitingList&)));
}

/**
 * Slot for when a specific Facility was updated
 * @param fac Facility that was updated
 */
void GetDataDisplayMapInterface::_receivedUpdatedFacility(Facility* fac)
{
    emit receivedUpdatedFacility(fac);
}

/**
 * Slot for when a specific Waiting List was updated
 * @param id Area ID that whose waiting list was updated
 * @param wl the WaitingList that was updated
 */
void GetDataDisplayMapInterface::_receivedUpdatedWaitingList(ID id, WaitingList& wl)
{
    emit receivedUpdatedWaitingList(id, wl);
}
