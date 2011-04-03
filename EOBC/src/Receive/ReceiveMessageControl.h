#ifndef RECEIVEMESSAGECONTROL_H
#define RECEIVEMESSAGECONTROL_H

#include "area.h"
#include "QFile"
#include "QLinkedList"
#include <QtXml/qdom.h>
#include "../Common/logger.h"

/**
 * @brief Parses messages received from other processes
 *
 * Turns XML tags into model objects
 *
 * This class is part of the Receive subsystem described in D2.
 */
class ReceiveMessageControl
{
public:
    void parseMessage(QByteArray qByte);
private:
    void parseAdd(QDomElement addTag);
    void parseDelete(QDomElement deleteTag);
    void parseResponse(QDomElement responseTag);
    void parseRequest(QDomElement RequestTag);
    void parseRebuild(QDomElement rebuildTag);
};

#endif // RECEIVEMESSAGECONTROL_H
