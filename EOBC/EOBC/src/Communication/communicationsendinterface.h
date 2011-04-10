#ifndef COMMUNICATIONSENDINTERFACE_H
#define COMMUNICATIONSENDINTERFACE_H

#include "channelout.h"

class CommunicationSendInterface
{
public:
    CommunicationSendInterface();
    ~CommunicationSendInterface();

    void sendMessage(QByteArray& data);

private:
    ChannelOut* _channelOut;
};

#endif // COMMUNICATIONSENDINTERFACE_H
