#ifndef AREA_H
#define AREA_H

#include "modelcontainer.h"
#include "facility.h"
#include "waitinglist.h"

class Area : public ModelContainer<Facility*>
{
public:
    Area(WaitingList* inList);
    virtual ~Area();

private:
    /// @todo figure out what to do with waiting list....?
    WaitingList* _list;

};

#endif // AREA_H
