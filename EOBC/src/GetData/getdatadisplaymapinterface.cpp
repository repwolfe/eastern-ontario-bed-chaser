#include "getdatadisplaymapinterface.h"

GetDataDisplayMapInterface::GetDataDisplayMapInterface(GetDataControl &getData) :
    _getData(getData)
{
    connect(&_getData, SIGNAL(receivedUpdatedFacility(Facility*)),
            SLOT(_receivedUpdatedFacility(Facility*)));
    connect(&_getData, SIGNAL(receivedUpdatedWaitingList(ID,WaitingList&)),
            SLOT(_receivedUpdatedWaitingList(ID,WaitingList&)));
}

void GetDataDisplayMapInterface::_receivedUpdatedFacility(Facility* fac)
{
    emit receivedUpdatedFacility(fac);
}

void GetDataDisplayMapInterface::_receivedUpdatedWaitingList(ID id, WaitingList& wl)
{
    emit receivedUpdatedWaitingList(id, wl);
}
