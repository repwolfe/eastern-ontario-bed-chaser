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
    Area();
    Area(FacilityList& facilities);
    Area(WaitingList& waitingList);
    Area(FacilityList& facilities, WaitingList& waitingList);
    ~Area();

    bool addFacility(Facility* inFacility);
    bool deleteFacility(ID& key);
    void setFacilities(FacilityList& inFacilities);
    Facility* getFacility(ID& key);

    bool addPatientToWaitingList(Patient* patient);
    bool removePatientFromWaitingList(QString& healthCardNum);
    void setWaitingList(WaitingList& inWaitingList);
    WaitingList& getWaitingList();

protected:
    void _deleteFacilities();
    void _deleteWaitingList();

    FacilityList _facilities;
    WaitingList _waitingList;
};

#endif // AREA_H

