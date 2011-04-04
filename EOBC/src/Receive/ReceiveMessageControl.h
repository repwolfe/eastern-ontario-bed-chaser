#ifndef RECEIVEMESSAGECONTROL_H
#define RECEIVEMESSAGECONTROL_H

#include "area.h"
#include "QFile"
#include "QLinkedList"
#include <QtXml/qdom.h>
#include "../Common/logger.h"
#include "convenience.h"

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
    void parseMessage(QByteArray qByte);
signals:
    void addBeds(ID sourceArea, ID sourceFacility, EOBC::CareType, int numOfBeds);
    void addPatient(ID areaID, ID facilityID, Patient* p);
    void deletePatient(ID areaID, ID facilityID,Patient* p);
    void sendRebuild(ID sourceArea, ID sourceFacility);
private:
    void parseAdd(QDomElement addTag);
    void parseDelete(QDomElement deleteTag);
    void parseAddDeleteRebuild(QDomElement tag, bool add, bool rebuild);
    void parseResponse(QDomElement responseTag);
    void parseRequest(QDomElement RequestTag);
    void parseRebuild(QDomElement rebuildTag);
};

#endif // RECEIVEMESSAGECONTROL_H
