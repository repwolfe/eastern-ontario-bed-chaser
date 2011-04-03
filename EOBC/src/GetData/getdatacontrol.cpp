#include "getdatacontrol.h"

GetDataControl::GetDataControl()
{
}

void GetDataControl::requestAllFacilities()
{
    /// @todo ask storage for all facilities

    /// @todo remove this
    QMap<ID, QString> facilities;
    facilities[1] = "Peter D Clark";
    facilities[2] = "Franklin General";
    facilities[3] = "Wolfram and Hart Institute";
    emit receivedAllFacilities(facilities);
}

void GetDataControl::requestFacilitiesPatients()
{
    /// @todo ask storage for all facilities' patients

    /// @todo remove this, MEMORY LEAK
    QMap<ID, QLinkedList<Patient*> > facilitiesPatients;
    QLinkedList<Patient*> list1;
    list1 << new Patient("1111-123-123", "Robbie", "Wolfe", EOBC::AC);
    list1 << new Patient("2222-123-123", "Austin", "Chamney", EOBC::LTC);
    list1 << new Patient("3333-123-123", "JP", "Landry", EOBC::CCC);
    facilitiesPatients[1] = list1;
    QLinkedList<Patient*> list2;
    list2 << new Patient("4444-123-123", "Ichigo", "Kurosaki", EOBC::CCC);
    list2 << new Patient("5555-123-123", "Naruto", "Uzumaki", EOBC::AC);
    facilitiesPatients[2] = list2;
    QLinkedList<Patient*> list3;
    list3 << new Patient("7777-123-123", "Lelouche", "Vi Britannia", EOBC::AC);
    list3 << new Patient("8888-123-123", "Luffy D.", "Monkey", EOBC::CCC);
    list3 << new Patient("9999-123-123", "Light", "Yagami", EOBC::CCC);
    facilitiesPatients[3] = list3;
    emit receivedFacilitiesPatients(facilitiesPatients);
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

