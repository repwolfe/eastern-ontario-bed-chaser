#include "getdatadisplaymapinterface.h"

GetDataDisplayMapInterface::GetDataDisplayMapInterface(GetDataControl &getData) :
    _getData(getData)
{
    connect(&_getData, SIGNAL(receivedUpdatedFacility(Facility*)),
            SLOT(_receivedUpdatedFacility(Facility*)));
    connect(&_getData, SIGNAL(receivedUpdatedWaitingList(ID,QLinkedList<Patient*>&)),
            SLOT(_receivedUpdatedWaitingList(ID,QLinkedList<Patient*>&)));
}

void GetDataDisplayMapInterface::_receivedUpdatedFacility(Facility* fac)
{
    emit receivedUpdatedFacility(fac);
}

void GetDataDisplayMapInterface::_receivedUpdatedWaitingList(ID id, QLinkedList<Patient*>& wl)
{
    emit receivedUpdatedWaitingList(id, wl);
}
