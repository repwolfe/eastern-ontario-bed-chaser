#ifndef AREA_H
#define AREA_H

#include "facility.h"

/// A list of Facilities
typedef QMap<ID,Facility*> FacilityList;

/// WaitingList defined in patient.h
/// FacilityList defined in facility.h

/**
 * @brief The object representation of an Area.
 *
 *Areas have a collection of Facility pointers, as well
 * as a waiting list of patients trying to get admitted
 * to this area.
 *
 * This class is part of the Model subsystem described in D2.
 */
class Area
{
public:
    Area(ID areaId);
    Area(ID areaId, FacilityList& facilities);
    Area(ID areaId, WaitingList& waitingList);
    Area(ID areaId, FacilityList& facilities, WaitingList& waitingList);
    ~Area();

    bool addFacility(Facility* inFacility);
    bool removeFacility(Facility* facility);
    bool removeFacility(ID key);
    void setFacilities(FacilityList& inFacilities);
    Facility* getFacility(ID key);
    FacilityList& getFacilities();

    bool addPatientToWaitingList(QString hcn, QString first, QString last, QDate placedOnWL);
    bool addPatientToWaitingList(Patient* patient);
    bool removePatientFromWaitingList(QString healthCardNum);
    void setWaitingList(WaitingList& inWaitingList);
    WaitingList& getWaitingList();
    QLinkedList<Patient*> getWaitingListAsList();

    ID getAreaId() const;
    void setAreaId(ID inId);

    bool isOurArea() const;
    void makeThisOurArea();

private:
    Area(const Area&);	// no implicit copy constructing
    void _deleteFacilities();
    void _deleteWaitingList();

    ID _id;
    FacilityList _facilities;
    WaitingList _waitingList;

    bool _isOurArea;
};

#endif // AREA_H

