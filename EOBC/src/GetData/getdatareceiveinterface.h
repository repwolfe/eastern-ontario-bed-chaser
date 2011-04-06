#ifndef GETDATARECEIVEINTERFACE_H
#define GETDATARECEIVEINTERFACE_H

#include <QObject>
#include "getdatacontrol.h"

/**
 * @brief Interface between the GetData and Receive subsystems
 *
 * Provides data needed by Receive forms to the subsystem without
 * revealing the internals of the database
 *
 * @todo traceability
 */
class GetDataReceiveInterface : public QObject
{
    Q_OBJECT
public:
    explicit GetDataReceiveInterface(GetDataControl& getData);

signals:
    void receivedFacilityRequest();
    //void receivedUpdatedWaitingList(ID, WaitingList&);

private slots:
    void _receivedFacilityRequest();
    //void _receivedUpdatedWaitingList(ID id, WaitingList& wl);

private:
    GetDataControl& _getData;

};

#endif // GETDATARECEIVEINTERFACE_H
