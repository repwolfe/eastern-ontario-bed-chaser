#include "storageread.h"
StorageRead::StorageRead(StorageHandler* handle)
{
    this->_storageHandler = handle;
    connect(handle,SIGNAL(facilityAdded(ID,Facility*)),this, SLOT(_addFacility(ID,Facility*)));
}
void StorageRead::_addFacility(ID sourceArea, Facility* f)
{
    Q_UNUSED(sourceArea);
    emit this->addFacility(f);
}

QMap<ID, QString> StorageRead::getAllFacilityNames()
{
    return _storageHandler->getFacilityNames();
}

QMap<ID, Facility*> StorageRead::getAllFacilityPointers()
{
    return _storageHandler->getFacilityPointers();
}

QMap<ID, Area*> StorageRead::getAllAreas()
{
    return _storageHandler->getAllAreas();
}

QMap<ID, QLinkedList<Patient*> > StorageRead::getAllPatients()
{
    return _storageHandler->getAllPatients();
}

QMap<ID, QLinkedList<Patient*> > StorageRead::getAllAreasWaitingList()
{
    return _storageHandler->getAllAreasWaitingList();
}

QMap<ID, QVector<int> > StorageRead::getTotalBeds() //AC, CCC, LTC
{
    return _storageHandler->getTotalBeds();
}

QMap<ID, QVector<int> > StorageRead::getOccupiedBeds()
{
    return _storageHandler->getOccupiedBeds();
}

Facility* StorageRead::getFacility(ID facID)
{
    return _storageHandler->getFacility(facID);
}

Facility* StorageRead::getCurrentFacility()
{
    return _storageHandler->getCurrentFacility();
}
