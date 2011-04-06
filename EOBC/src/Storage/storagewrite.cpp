#include "storagewrite.h"

StorageWrite::StorageWrite(StorageHandler* sh)
{
    _sHandler = sh;
}

void StorageWrite::addBeds(ID sourceArea, ID sourceFacility, EOBC::CareType, int numOfBeds)
{
    //_sHandler->addbeds();
}

void StorageWrite::removeBeds(ID sourceArea, ID sourceFacility, EOBC::CareType, int numOfBeds)
{
   //_sHandler->removeBeds();
}

void StorageWrite::addPatient(ID areaID, ID facilityID, Patient* p)
{
    _sHandler->addPatient(areaID,facilityID,p);
}

void StorageWrite::deletePatient(ID areaID, ID facilityID,Patient* p)
{
    _sHandler->deletePatient(areaID,facilityID,p);
}

void StorageWrite::sendRebuild(ID sourceArea, ID sourceFacility)
{
  //  _sHandler->sendRebuild();
}

void StorageWrite::addFacility(ID sourceArea, Facility* f)
{

}
