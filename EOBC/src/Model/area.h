#ifndef AREA_H
#define AREA_H

#include "modelcontainer.h"
#include "facility.h"
#include "waitinglist.h"

/**
 * Areas have a collection of Facility pointers, as well
 * as a waiting list of patients trying to get admitted
 * to this area.
 *
 * This class is part of the Model subsystem described in D2.
 */
class Area : public ModelContainer<QString,Facility*>
{
public:
    Area(WaitingList* inList);
    virtual ~Area();

private:
    /// @todo figure out what to do with waiting list....?
    WaitingList* _list;

};

#endif // AREA_H
