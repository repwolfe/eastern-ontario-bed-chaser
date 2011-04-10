#include "storagewrite.h"

StorageWrite::StorageWrite(StorageHandler* sh)
{
    _sHandler = sh;
}

void StorageWrite::addBeds(ID sourceArea, ID sourceFacility, EOBC::CareType type, int numOfBeds)
{
    Facility* facility = _sHandler->getFacility(sourceArea, sourceFacility);
    if (facility)
    {
	facility->addBeds(numOfBeds, type);
        _sHandler->updateBeds(sourceArea,sourceFacility);
    }
}

void StorageWrite::removeBeds(ID sourceArea, ID sourceFacility, EOBC::CareType type, int numOfBeds)
{
    Facility* facility = _sHandler->getFacility(sourceArea, sourceFacility);
    if (facility)
    {
	facility->decreaseBeds(numOfBeds, type);
        _sHandler->updateBeds(sourceArea,sourceFacility);
    }
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

void StorageWrite::addFacility(ID sourceArea, Facility* f,bool remote)
{
    _sHandler->addFacility(sourceArea, f,remote);
}
