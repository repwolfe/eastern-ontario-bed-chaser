#include "getdatachangedatainterface.h"

GetDataChangeDataInterface::GetDataChangeDataInterface(GetDataControl &getData) :
    _getData(getData)
{
    connect(&_getData, SIGNAL(receivedAllFacilityPointers(QMap<ID,Facility*>)),
	    SLOT(_receivedAllFacilityPointers(QMap<ID,Facility*>)));
    connect(&_getData, SIGNAL(receivedAllAreaPointers(QMap<ID,Area*>)),
	    SLOT(_receivedAllAreaPointers(QMap<ID,Area*>)));
    connect(&_getData, SIGNAL(receivedAreasWaitingList(QMap<ID,QLinkedList<Patient*> >)),
            SLOT(_receivedAreasWaitingList(QMap<ID,QLinkedList<Patient*> >)));
    connect(&_getData, SIGNAL(receivedFacilitiesPatients(QMap<ID,QLinkedList<Patient*> >)),
            SLOT(_receivedFacilitiesPatients(QMap<ID,QLinkedList<Patient*> >)));
    connect(&_getData, SIGNAL(receivedFacilitiesCurrentBedNumbers(QMap<ID,QVector<int> >)),
            SLOT(_receivedFacilitiesCurrentBedNumbers(QMap<ID,QVector<int> >)));
    connect(&_getData, SIGNAL(receivedFacilitiesMinimumBedNumbers(QMap<ID,QVector<int> >)),
            SLOT(_receivedFacilitiesMinimumBedNumbers(QMap<ID,QVector<int> >)));
    connect(&_getData, SIGNAL(receivedFacilityWithID(Facility*)),
	    SLOT(_receivedFacilityWithID(Facility*)));
}

void GetDataChangeDataInterface::requestAllFacilityPointers()
{
    _getData.requestAllFacilityPointers();
}

void GetDataChangeDataInterface::requestAllAreaPointers()
{
    _getData.requestAllAreaPointers();
}

void GetDataChangeDataInterface::requestFacilitiesPatients()
{
    _getData.requestFacilitiesPatients();
}

void GetDataChangeDataInterface::requestAreasWaitingList()
{
    _getData.requestAreasWaitingList();
}

void GetDataChangeDataInterface::requestFacilitiesCurrentBedNumbers()
{
    _getData.requestFacilitiesCurrentBedNumbers();
}

void GetDataChangeDataInterface::requestFacilitiesMinimumBedNumbers()
{
    _getData.requestFacilitiesMinimumBedNumbers();
}

void GetDataChangeDataInterface::requestFacilityWithID(ID id)
{
    _getData.requestFacilityWithID(id);
}

/**
 * Slot for when received all the facilities
 * @param data map of Facility ID to Name
 */
void GetDataChangeDataInterface::_receivedAllFacilityPointers(const QMap<ID, Facility*>& data)
{
    emit receivedAllFacilityPointers(data);
}

/**
 * Slot for when received all the areas
 * @param data map of Area ID to Area*
 */
void GetDataChangeDataInterface::_receivedAllAreaPointers(const QMap<ID, Area*> &data)
{
    emit receivedAllAreaPointers(data);
}

/**
 * Slot for when received all the facilities patients
 * @param data map of Facility ID to list of Patient objects
 */
void GetDataChangeDataInterface::_receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient *> > &data)
{
    emit receivedFacilitiesPatients(data);
}

/**
 * Slot for when received all areas waiting list
 * @param data map of Area ID to a list of Patient objects
 */
void GetDataChangeDataInterface::_receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient *> > &data)
{
    emit receivedAreasWaitingList(data);
}

/**
 * Slot for when received current bed numbers
 * @param data map of Facility ID to a Vector of bed numbers
 */
void GetDataChangeDataInterface::_receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> > &data)
{
    emit receivedFacilitiesCurrentBedNumbers(data);
}

/**
 * Slot for when received minimum bed numbers
 * @param data map of Facility ID to a Vector of bed numbers
 */
void GetDataChangeDataInterface::_receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> > &data)
{
    emit receivedFacilitiesMinimumBedNumbers(data);
}

/**
 * Slot for when a specific Facility which was requested is received
 * @param fac Facility that was requested
 */
void GetDataChangeDataInterface::_receivedFacilityWithID(Facility *fac)
{
    emit receivedFacilityWithID(fac);
}
