#ifndef COMMUNICATIONSENDINTERFACE_H
#define COMMUNICATIONSENDINTERFACE_H

#include "sendmessagecontrol.h"

class CommunicationSendInterface : public QObject
{
    Q_OBJECT
public:
    CommunicationSendInterface(SendMessageControl& sendMessage);

    void sendMessage(QByteArray& data);


private:
    SendMessageControl& _sendMessage;
};

#endif // COMMUNICATIONSENDINTERFACE_H
