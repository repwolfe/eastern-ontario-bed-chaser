#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include "modelcontainer.h"
#include "patient.h"

/**
 * WaitingLists are a collection of patient's waiting to
 * get admitted to a particular area.
 *
 * This class is part of the Model subsystem described in D2.
 */
class WaitingList : public ModelContainer<QString,Patient*>
{
public:

private:

};

#endif // WAITINGLIST_H
