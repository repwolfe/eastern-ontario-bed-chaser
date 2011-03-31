#ifndef STORAGEHANDLER_H
#define STORAGEHANDLER_H

#include "area.h"
#include "QFile"
#include "QLinkedList"
#include <QtXml/qdom.h>
#include "../Common/logger.h"

/**
 * StorageHandler has a collection of Areas and uses an xml file
 * for persistant storage
 *
 * This class is part of the Storage subsystem described in D2.
 */
typedef QMap<int,Area*> areaList;
class StorageHandler
{
public:
    StorageHandler(QString fileName);
    virtual ~StorageHandler();
    int loadModel(QString fileName);
    int saveModel(QString fileName, Area* anArea, int facilityID);

    Facility* getFacility(ID areaID, ID facilityID);
    QList<Patient*> getWaitingList(ID areaID);
    QList<Patient*> getPatients(ID areaID, ID facilityID, EOBC::CareType reqCare);
    QList<Patient*> getPatients(ID areaID, ID facilityID);

protected:
    Facility* _currentFacility;
    Area* _currentArea;
    areaList _areas;

private:
   Area* _getArea(ID id);
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
