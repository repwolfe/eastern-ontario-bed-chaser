#ifndef CHANGEDATARECEIVEINTERFACE_H
#define CHANGEDATARECEIVEINTERFACE_H

#include <QObject>
#include "ReceiveMessageControl.h"
#include "storagewrite.h"

/**
 * @brief Interface between the ChangeData and Receive subsystems
 *
 * Provides data needed by ChangeData forms to the subsystem without
 * revealing the internals of the database
 *
 * This class is part of the ChangeData subsystem described in D2.
 */
class ChangeDataReceiveInterface : public QObject
{
    Q_OBJECT
public:
    ChangeDataReceiveInterface(StorageWrite& sw,ReceiveMessageControl& rc );

signals:



private slots:
    void _addBeds(ID sourceArea, ID sourceFacility, EOBC::CareType, int numOfBeds);
    void _removeBeds(ID sourceArea, ID sourceFacility, EOBC::CareType, int numOfBeds);
    void _addPatient(ID areaID, ID facilityID, Patient* p);
    void _deletePatient(ID areaID, ID facilityID,Patient* p);
    void _sendRebuild(ID sourceArea, ID sourceFacility);
    void _addFacility(ID sourceArea, Facility* f,bool);
private:
    StorageWrite& _sw;

};

#endif // CHANGEDATARECEIVEINTERFACE_H
