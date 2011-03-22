#ifndef AREA_H
#define AREA_H

#include "facility.h"

#include <QMap>

/**
 * Areas have a collection of Facility pointers, as well
 * as a waiting list of patients trying to get admitted
 * to this area.
 *
 * This class is part of the Model subsystem described in D2.
 */
typedef int ID;
typedef QMap<ID,Facility*> FacilityList;
typedef QMap<QString, Patient*> WaitingList;

class Area
{
public:
    Area(ID areaId);
    Area(ID areaId, FacilityList& facilities);
    Area(ID areaId, WaitingList& waitingList);
    Area(ID areaId, FacilityList& facilities, WaitingList& waitingList);
    ~Area();

    bool addFacility(Facility* inFacility);
    bool deleteFacility(ID& key);
    void setFacilities(FacilityList& inFacilities);
    Facility* getFacility(ID& key);

    bool addPatientToWaitingList(Patient* patient);
    bool removePatientFromWaitingList(QString& healthCardNum);
    void setWaitingList(WaitingList& inWaitingList);
    WaitingList& getWaitingList();

    ID getAreaId() const;
    void setAreaId(ID inId);

protected:
    void _deleteFacilities();
    void _deleteWaitingList();

    ID _id;
    FacilityList _facilities;
    WaitingList _waitingList;
};

#endif // AREA_H

