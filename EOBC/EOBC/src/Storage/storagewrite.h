#ifndef STORAGEWRITE_H
#define STORAGEWRITE_H
#include "area.h"

#include "storageHandler.h"

class StorageWrite : public QObject
{
    Q_OBJECT
public:
    StorageWrite(StorageHandler* sh);
    void addBeds(ID sourceArea, ID sourceFacility, EOBC::CareType, int numOfBeds);
    void removeBeds(ID sourceArea, ID sourceFacility, EOBC::CareType, int numOfBeds);
    void addPatient(ID areaID, ID facilityID, Patient* p);
    void deletePatient(ID areaID, ID facilityID,Patient* p);
    void sendRebuild(ID sourceArea, ID sourceFacility);
    void addFacility(ID sourceArea, Facility* f,bool remote);
signals:

public slots:
private:
    StorageHandler* _sHandler;

};

#endif // STORAGEWRITE_H
