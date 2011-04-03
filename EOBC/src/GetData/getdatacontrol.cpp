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

void GetDataControl::requestAllAreas()
{
    /// @todo ask storage for all facilities

    /// @todo remove this
    QMap<ID, QString> facilities;
    facilities[1] = "North Lanark";
    facilities[2] = "Renfrew County";
    facilities[3] = "Ottawa West";
    emit receivedAllAreas(facilities);
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

    /// @todo remove this, MEMORY LEAK

    QMap<ID, QLinkedList<Patient*> > areasWaitingList;
    QLinkedList<Patient*> list1;
    list1 << new Patient("1111-123-123", "Robbie", "Wolfe", EOBC::AC);
    list1 << new Patient("2222-123-123", "Austin", "Chamney", EOBC::LTC);
    list1 << new Patient("3333-123-123", "JP", "Landry", EOBC::CCC);
    areasWaitingList[1] = list1;
    QLinkedList<Patient*> list2;
    list2 << new Patient("4444-123-123", "Ichigo", "Kurosaki", EOBC::CCC);
    list2 << new Patient("5555-123-123", "Naruto", "Uzumaki", EOBC::AC);
    areasWaitingList[2] = list2;
    QLinkedList<Patient*> list3;
    list3 << new Patient("7777-123-123", "Lelouche", "Vi Britannia", EOBC::AC);
    list3 << new Patient("8888-123-123", "Luffy D.", "Monkey", EOBC::CCC);
    list3 << new Patient("9999-123-123", "Light", "Yagami", EOBC::CCC);
    areasWaitingList[3] = list3;

    emit receivedAreasWaitingList(areasWaitingList);
}

void GetDataControl::requestFacilitiesCurrentBedNumbers()
{
    /// @todo ask all facilities' for their current bed numbers

    /// @todo remove this
    QMap<ID, QVector<int> > beds;
    beds[1] = QVector<int>() << 20 << 30 << 0;
    beds[2] = QVector<int>() << 4 << 17 << 0;
    beds[3] = QVector<int>() << 0 << 0 << 24;
    emit receivedFacilitiesCurrentBedNumbers(beds);
}

void GetDataControl::requestFacilitiesMinimumBedNumbers()
{
    /// @todo ask all facilities' for their minimum bed numbers

    /// @todo remove this
    QMap<ID, QVector<int> > beds;
    beds[1] = QVector<int>() << 13 << 12 << 0;
    beds[2] = QVector<int>() << 1 << 10 << 0;
    beds[3] = QVector<int>() << 0 << 0 << 20;
    emit receivedFacilitiesMinimumBedNumbers(beds);
}

void GetDataControl::requestReport(QDate fromDate, QDate toDate, ID facId, QString constraints)
{
    /// @todo ask for report data

    /// @todo remove
    Q_UNUSED(constraints)
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
    for (int i = 0; i <= barnum; ++i) { list1 << rand() % 20; list2 << rand() % 20; }
    QPair<QString, QLinkedList<int> > data1 = qMakePair(tr("AC"), list1);
    QPair<QString, QLinkedList<int> > data2 = qMakePair(tr("AC"), list2);
    emit receivedReport(fromDate, toDate, facId, data1, data2);
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
 * Slot for when received all the areas
 * @param data map of Area ID to Name
 */
void GetDataControl::_receivedAllAreas(const QMap<ID, QString> & data)
{
    emit receivedAllAreas(data);
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
void GetDataControl::_receivedUpdatedFacility(Facility* fac)
{
    emit receivedUpdatedFacility(fac);
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

