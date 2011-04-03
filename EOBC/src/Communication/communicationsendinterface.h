#ifndef COMMUNICATIONSENDINTERFACE_H
#define COMMUNICATIONSENDINTERFACE_H

#include "sendmessagecontrol.h"
#include "channelout.h"

class CommunicationSendInterface : public QObject
{
    Q_OBJECT
public:
    CommunicationSendInterface(SendMessageControl& sendMessage);
    ~CommunicationSendInterface();

public slots:
    void sendMessage(QByteArray& data);


private:
    SendMessageControl& _sendMessage;
    ChannelOut* _channelOut;
};

#endif // COMMUNICATIONSENDINTERFACE_H
