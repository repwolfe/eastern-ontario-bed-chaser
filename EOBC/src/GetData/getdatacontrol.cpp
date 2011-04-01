#include "getdatacontrol.h"

GetDataControl::GetDataControl()
{
}

void GetDataControl::requestAllFacilities()
{
    /// @todo ask storage for all facilities
}

void GetDataControl::requestFacilitiesPatients()
{
    /// @todo ask storage for all facilities' patients
}

void GetDataControl::requestAreasWaitingList()
{
    /// @todo ask storage for all facilities' waiting list
}

void GetDataControl::requestFacilitiesCurrentBedNumbers()
{
    /// @todo ask all facilities' for their current bed numbers
}

void GetDataControl::requestFacilitiesMinimumBedNumbers()
{
    /// @todo ask all facilities' for their minimum bed numbers
}

void GetDataControl::_receivedAllFacilities(const QMap<ID, QString> & data)
{
    emit receivedAllFacilities(data);
}

void GetDataControl::_receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient *> > &data)
{
    emit receivedFacilitiesPatients(data);
}

void GetDataControl::_receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient *> > &data)
{
    emit receivedAreasWaitingList(data);
}

void GetDataControl::_receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> > &data)
{
    emit receivedFacilitiesCurrentBedNumbers(data);
}

void GetDataControl::_receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> > &data)
{
    emit receivedFacilitiesMinimumBedNumbers(data);
}

void GetDataControl::_receivedUpdatedFacility(Facility* fac)
{
    emit receivedUpdatedFacility(fac);
}

void GetDataControl::_receivedUpdatedWaitingList(ID id, WaitingList& wl)
{
    emit receivedUpdatedWaitingList(id, wl);
}

