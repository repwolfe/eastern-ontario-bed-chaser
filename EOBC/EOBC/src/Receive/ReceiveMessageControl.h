#ifndef RECEIVEMESSAGECONTROL_H
#define RECEIVEMESSAGECONTROL_H

#include "area.h"
#include <QLinkedList>
#include <QtXml/qdom.h>
#include "logger.h"
#include "convenience.h"
#include "communicationreceiveinterface.h"
#include "getdatareceiveinterface.h"

/**
 * @brief Parses messages received from other EOBC nodes
 *
 * Turns XML tags into model objects
 *
 * This class is part of the Receive subsystem described in D2.
 */
class ReceiveMessageControl : public QObject
{
    Q_OBJECT
public:
    ReceiveMessageControl(CommunicationReceiveInterface& receiveData, GetDataReceiveInterface& recInter);

signals:
    void addBeds(ID sourceArea, ID sourceFacility, EOBC::CareType, int numOfBeds);
    void removeBeds(ID sourceArea, ID sourceFacility, EOBC::CareType, int numOfBeds);
    void addPatient(ID areaID, ID facilityID, Patient* p);
    void deletePatient(ID areaID, ID facilityID,Patient* p);
    void sendRebuild(ID sourceArea, ID sourceFacility);
    void addFacility(ID sourceArea, Facility* f,bool remote);
    void receivedFacilityRequest();

private slots:
    void _parseMessage(QByteArray& qByte);

private:
    void parseAdd(QDomElement addTag);
    void parseDelete(QDomElement deleteTag);
    void parseAddDeleteRebuild(QDomElement tag, bool add, bool rebuild);
    void parseResponse(QDomElement responseTag);
    void parseRequest(QDomElement RequestTag);
    void parseRebuild(QDomElement rebuildTag);
};

#endif // RECEIVEMESSAGECONTROL_H
