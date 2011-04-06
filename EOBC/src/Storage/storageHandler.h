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
class StorageHandler : public QObject
{
    Q_OBJECT
public:
    StorageHandler(QString fileName);
    virtual ~StorageHandler();
    int loadModel(QString fileName);
    int saveModel(QString fileName, Area* anArea, int facilityID);

    //read Methods
    QMap<ID, Area*> getModel();
    Facility* getFacility(ID areaID, ID facilityID);
    WaitingList getWaitingList(ID areaID);
    PatientContainer* getPatients(ID areaID, ID facilityID, EOBC::CareType reqCare);
    PatientContainer* getPatients(ID areaID, ID facilityID);

    //write Methods
    QString getFileName();
    void addPatient(ID areaID, ID facilityID, Patient* p);
    void addPatient(ID areaID, Patient* p);
    void addFacility(ID areaID, Facility* f);
    void deletePatient(ID areaID, ID facilityID, Patient* p);
    void deletePatient(ID areaID, Patient* p);

    Facility* getCurrentFacility();
    Area* getCurrentArea();

protected:
    Facility* _currentFacility;
    Area* _currentArea;
    areaList _areas;

private:
   Area* _getArea(ID id);
   Facility* _getFacility(ID areaID, ID facilityID);


   QLinkedList<Area*> _model;
   QString _filename;
   void parseWaitingList(Area* anArea,QDomNode* n);
   void parseFacility(Facility* aFacility,QDomNode* n);
   areaList getAreas();

   QDomElement* saveWaitingList(Area* anArea);
   QDomElement* saveFacility(Facility* facility);
   QDomElement* saveArea(Area* area);

signals:
   void facilityAdded(ID areaID, Facility* f);

};

#endif // STORAGEHANDLER_H
