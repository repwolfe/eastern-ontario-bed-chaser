#include "storageread.h"
StorageRead::StorageRead(StorageHandler* handle)
{
    this->_storageHandler = handle;
    connect(handle,SIGNAL(facilityAdded(ID,Facility*)),this, SLOT(_addFacility(ID,Facility*)));
}
void StorageRead::_addFacility(ID sourceArea, Facility* f)
{
    emit this->addFacility(f);
}

/*QMap<ID, Area*> StorageRead::getAllAreas()
{
    return _storageHandler->getModel();
}

QMap<ID, QString> StorageRead::getAllFacilityNames()
{
    return _storageHandler->getFacility()
}
Facility StorageRead::getFacility(ID facID)
{

}

QMap<ID, Facility*> StorageRead::getAllFacilities()
{

}

QMap<ID, QLinkedList<Patient*> > StorageRead::getAllPatients();
*/
