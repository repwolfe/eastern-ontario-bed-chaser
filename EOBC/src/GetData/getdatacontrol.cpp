#include "getdatacontrol.h"
GetDataControl::GetDataControl(StorageRead& sr, SendGetDataInterface& sendGetDataI) : _storage(sr), _sendGetDataI(sendGetDataI)
{
    connect(&sr,SIGNAL(addFacility(Facility*,bool)),this,SLOT(_receivedUpdatedFacility(Facility*,bool)));

}

void GetDataControl::requestAllFacilities()
{
    const QMap<ID, QString>& facilities = _storage.getAllFacilityNames();
    emit receivedAllFacilities(facilities);
}

void GetDataControl::requestAllFacilityPointers()
{
    const QMap<ID, Facility*>& facilities = _storage.getAllFacilityPointers();
    emit receivedAllFacilityPointers(facilities);
}

void GetDataControl::requestAllAreaPointers()
{
    const QMap<ID, Area*>& facilities = _storage.getAllAreas();
    emit receivedAllAreaPointers(facilities);
}

void GetDataControl::requestFacilitiesPatients()
{
    const QMap<ID, QLinkedList<Patient*> >& facilitiesPatients = _storage.getAllPatients();
    emit receivedFacilitiesPatients(facilitiesPatients);
}

void GetDataControl::requestAreasWaitingList()
{
    const QMap<ID, QLinkedList<Patient*> >& areasWaitingList = _storage.getAllAreasWaitingList();
    emit receivedAreasWaitingList(areasWaitingList);
}

void GetDataControl::requestFacilitiesCurrentBedNumbers()
{
    const QMap<ID, QVector<int> >& beds = _storage.getTotalBeds();
    emit receivedFacilitiesCurrentBedNumbers(beds);
}

void GetDataControl::requestFacilitiesMinimumBedNumbers()
{
    const QMap<ID, QVector<int> >& beds = _storage.getOccupiedBeds();
    emit receivedFacilitiesMinimumBedNumbers(beds);
}

void GetDataControl::requestReport(QDate fromDate, QDate toDate, ID facId, QString constraints)
{
    /// @todo ask for real report data

    /// @todo remove
    Q_UNUSED(constraints)

    // Fake data for reports
    int barnum = 0;
    if(toDate.month() - fromDate.month() == 0)
    {
	barnum= toDate.day() - fromDate.day();
    }
    else if(toDate.year() - fromDate.year() == 0)
    {
	barnum= toDate.month() - fromDate.month();
    }
    else
    {
	barnum= toDate.year() - fromDate.year();
    }

    QLinkedList<int> list1;
    QLinkedList<int> list2;
    list1 << rand() % 20;
    list2 << rand() % 20;
    for (int i = 1; i <= barnum; ++i) { list1 << rand() % 10 -5; list2 << rand() % 10 - 5; }
    QPair<QString, QLinkedList<int> > data1 = qMakePair(tr("AC"), list1);
    QPair<QString, QLinkedList<int> > data2 = qMakePair(tr("AC"), list2);
    emit receivedReport(fromDate, toDate, facId, data1, data2);
}

void GetDataControl::requestFacilityWithID(ID id)
{
    Facility* facility = _storage.getFacility(id);
    emit receivedFacilityWithID(facility);
}

/**
 * Slot for when received all the facilities
 * @param data map of Facility ID to Name
 */
void GetDataControl::_receivedAllFacilities(const QMap<ID, QString> & data)
{
    emit receivedAllFacilities(data);
}

/**
 * Slot for when received all the facility pointers
 * @param data map of Facility ID to Pointer
 */
void GetDataControl::_receivedAllFacilityPointers(const QMap<ID, Facility*>& data)
{
    emit receivedAllFacilityPointers(data);
}

/**
 * Slot for when received all the areas
 * @param data map of Area ID to Area*
 */
void GetDataControl::_receivedAllAreaPointers(const QMap<ID, Area*> & data)
{
    emit receivedAllAreaPointers(data);
}

/**
 * Slot for when received all the facilities patients
 * @param data map of Facility ID to list of Patient objects
 */
void GetDataControl::_receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient *> > &data)
{
    emit receivedFacilitiesPatients(data);
}

/**
 * Slot for when received all areas waiting list
 * @param data map of Area ID to a list of Patient objects
 */
void GetDataControl::_receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient *> > &data)
{
    emit receivedAreasWaitingList(data);
}

/**
 * Slot for when received current bed numbers
 * @param data map of Facility ID to a Vector of bed numbers
 */
void GetDataControl::_receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> > &data)
{
    emit receivedFacilitiesCurrentBedNumbers(data);
}

/**
 * Slot for when received minimum bed numbers
 * @param data map of Facility ID to a Vector of bed numbers
 */
void GetDataControl::_receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> > &data)
{
    emit receivedFacilitiesMinimumBedNumbers(data);
}

/**
 * Slot for when a specific Facility was updated
 * @param fac Facility that was updated
 */
void GetDataControl::_receivedUpdatedFacility(Facility* fac,bool remote)
{
    emit receivedUpdatedFacility(fac,remote);
}

void GetDataControl::receivedFacilityRequest()
{
    _sendGetDataI.sendFacility(_storage.getCurrentFacility());
}

/**
 * Slot for when a specific Waiting List was updated
 * @param id Area ID that whose waiting list was updated
 * @param wl the WaitingList that was updated
 */
void GetDataControl::_receivedUpdatedWaitingList(ID id, WaitingList& wl)
{
    emit receivedUpdatedWaitingList(id, wl);
}

void GetDataControl::_receivedReport(QDate start, QDate end, ID facId, QPair<QString, QLinkedList<int> > &data, QPair<QString, QLinkedList<int> > &data2)
{
    emit receivedReport(start, end, facId, data, data2);
}

/**
 * Slot for when a specific Facility which was requested is received
 * @param fac Facility that was requested
 */
void GetDataControl::_receivedFacilityWithID(Facility* fac)
{
    emit receivedFacilityWithID(fac);
}

