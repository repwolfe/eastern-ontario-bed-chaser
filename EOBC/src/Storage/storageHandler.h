#ifndef STORAGEHANDLER_H
#define STORAGEHANDLER_H

#include "area.h"
#include "QFile"
#include "QLinkedList"
#include <QtXml/qdom.h>
#include "../Common/logger.h"



typedef QMap<ID,Area*> areaList;
/**
 * @brief Handles saving and loading of all persistant data
 *
 * StorageHandler has a collection of Areas and uses an xml file
 * for persistant storage
 *
 * This class is part of the Storage subsystem described in D2.
 */
class StorageHandler
{
public:
    StorageHandler(QString fileName);
    virtual ~StorageHandler();
    int loadModel(QString fileName);
    int saveModel(QString fileName, Area* anArea, int facilityID);

    //read Methods
    Facility* getFacility(ID areaID, ID facilityID);
    WaitingList getWaitingList(ID areaID);
    PatientContainer* getPatients(ID areaID, ID facilityID, EOBC::CareType reqCare);
    PatientContainer* getPatients(ID areaID, ID facilityID);

    //write Methods
    void addPatient(ID areaID, ID facilityID, Patient* p);
    void addPatient(ID areaID, Patient* p);
    void deletePatient(ID areaID, ID facilityID, Patient* p);
    void deletePatient(ID areaID, Patient* p);

protected:
    Facility* _currentFacility;
    Area* _currentArea;
    areaList _areas;

private:
   Area* _getArea(ID id);
   Facility* _getFacility(ID areaID, ID facilityID);

   StorageHandler _StorageHandler();
   QLinkedList<Area*> _model;
   void parseWaitingList(Area* anArea,QDomNode* n);
   void parseFacility(Facility* aFacility,QDomNode* n);
   areaList getAreas();

   QDomElement* saveWaitingList(Area* anArea);
   QDomElement* saveFacility(Facility* facility);
   QDomElement* saveArea(Area* area);

};

#endif // STORAGEHANDLER_H
