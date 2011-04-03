#ifndef GETDATADISPLAYMAPINTERFACE_H
#define GETDATADISPLAYMAPINTERFACE_H

#include <QObject>
#include "getdatacontrol.h"

/**
 * @brief Interface between the GetData and DisplayMap subsystems
 *
 * Provides data needed by DisplayMap forms to the subsystem without
 * revealing the internals of the database
 *
 * @todo traceability
 */
class GetDataDisplayMapInterface : public QObject
{
    Q_OBJECT
public:
    explicit GetDataDisplayMapInterface(GetDataControl& getData);

signals:
    void receivedUpdatedFacility(Facility*);
    void receivedUpdatedWaitingList(ID, WaitingList&);

private slots:
    void _receivedUpdatedFacility(Facility* fac);
    void _receivedUpdatedWaitingList(ID id, WaitingList& wl);

private:
    GetDataControl& _getData;

};

#endif // GETDATADISPLAYMAPINTERFACE_H
