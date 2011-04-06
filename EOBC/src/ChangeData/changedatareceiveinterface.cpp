#include "changedatareceiveinterface.h"

ChangeDataReceiveInterface::ChangeDataReceiveInterface(StorageWrite& sw, ReceiveMessageControl& rc ) :
           _sw(sw)
{
    connect(&rc,SIGNAL(addBeds(ID,ID,EOBC::CareType,int)),this,SLOT(_addBeds(ID,ID,EOBC::CareType,int)));
    connect(&rc,SIGNAL(addFacility(ID,Facility*)),this,SLOT(_addFacility(ID,Facility*)));
    connect(&rc,SIGNAL(addPatient(ID,ID,Patient*)),this,SLOT(_addPatient(ID,ID,Patient*)));
    connect(&rc,SIGNAL(removeBeds(ID,ID,EOBC::CareType,int)),this,SLOT(_removeBeds(ID,ID,EOBC::CareType,int)));
    connect(&rc,SIGNAL(sendRebuild(ID,ID)),this,SLOT(_sendRebuild(ID,ID)));
}


//
///SLOTS
//
void ChangeDataReceiveInterface::_addBeds(ID sourceArea, ID sourceFacility, EOBC::CareType ct, int numOfBeds)
{
    _sw.addBeds(sourceArea,sourceFacility,ct,numOfBeds);
}

void ChangeDataReceiveInterface::_removeBeds(ID sourceArea, ID sourceFacility, EOBC::CareType ct, int numOfBeds)
{
    _sw.removeBeds(sourceArea,sourceFacility,ct,numOfBeds);
}

void ChangeDataReceiveInterface::_addPatient(ID areaID, ID facilityID, Patient* p)
{
    _sw.addPatient(areaID,facilityID,p);
}

void ChangeDataReceiveInterface::_deletePatient(ID areaID, ID facilityID,Patient* p)
{
    _sw.deletePatient(areaID,facilityID,p);
}

void ChangeDataReceiveInterface::_sendRebuild(ID sourceArea, ID sourceFacility)
{
   _sw.sendRebuild(sourceArea, sourceFacility);
}

void ChangeDataReceiveInterface::_addFacility(ID sourceArea, Facility* f)
{
    _sw.addFacility(sourceArea,f);
}
